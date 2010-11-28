/*
 *  KernelEx
 *  Copyright(C) 2010, Tihiy
 *
 *  This file is part of KernelEx source code.
 *
 *  KernelEx is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation; version 2 of the License.
 *
 *  KernelEx is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <windows.h>
#include <stdio.h>
#include <shlwapi.h>
#include <map>
#include "sdbapi.h"
#include "wstring.hpp"

using namespace std;

typedef void (*STRPROC) (LPWSTR);

static int sections;
static PDB pdb;
static LPWSTR sdbfile;
static WCHAR inifile[MAX_PATH];
static FILE *regfile;
static map<wstring, TAGID> tagidmap;

void fail()
{
    SdbCloseDatabase(pdb);
    DeleteFileW(sdbfile);
    exit(-1);
}

void WriteTransform(LPWSTR section)
{
    //query file name
    WCHAR filebuf[MAX_PATH];
    WCHAR filepath[MAX_PATH];
    WCHAR name[MAX_PATH];

    if (!GetPrivateProfileStringW(section, L"Transform", NULL, filebuf, MAX_PATH, inifile))
	{
		printf("Section %ls does not specify file!\n", section);
		fail();
    }
    
	//build path to file relative to ini
    lstrcpyW(filepath, inifile);
    PathRemoveFileSpecW(filepath);
    PathAppendW(filepath, filebuf);
    
	LPWSTR filename = PathFindFileNameW(filepath);

    lstrcpyW(name, filepath);
    PathRemoveExtensionW(name);
    PathStripPathW(name);

    if (tagidmap.count(name) > 0)
		return;			//already have it

    printf("Adding %ls...", filepath);

    //write FILE
    TAGID filetagid = SdbBeginWriteListTag(pdb, TAG_FILE);
    SdbWriteStringTag(pdb, TAG_NAME, filename);
    if (SdbWriteBinaryTagFromFile(pdb, TAG_FILE_BITS, filepath))
		printf("Success!\n");
    else
	{
		printf("Failure!\n");
		fail();
    }
    SdbEndWriteListTag(pdb, filetagid);

    //write MSI_TRANSFORM
    TAGID transfid = SdbBeginWriteListTag(pdb, TAG_MSI_TRANSFORM);
    SdbWriteStringTag(pdb, TAG_NAME, name);
    SdbWriteStringTag(pdb, TAG_MSI_TRANSFORM_FILE, filename);
    SdbWriteDWORDTag(pdb, TAG_MSI_TRANSFORM_TAGID, filetagid);
    SdbEndWriteListTag(pdb, transfid);

    //add transform tagid to name - tagid map
	tagidmap[name] = transfid;
}

void WritePackage(LPWSTR section)
{
    //query file name
    WCHAR filebuf[MAX_PATH];
    WCHAR filepath[MAX_PATH];
    WCHAR name[MAX_PATH];

    GetPrivateProfileStringW(section, L"Transform", NULL, filebuf, MAX_PATH, inifile);

    //build path to file relative to ini
    lstrcpyW(filepath, inifile);
    PathRemoveFileSpecW(filepath);
    PathAppendW(filepath, filebuf);

    LPWSTR filename = PathFindFileNameW(filepath);

    lstrcpyW(name, filepath);
    PathRemoveExtensionW(name);
    PathStripPathW(name);

    TAGID transfid = tagidmap[name];

    //query attributes
    WCHAR appname[200];
    WCHAR packagecode[100];
    GUID guid;

    GetPrivateProfileStringW(section, L"AppName", section, appname, 200, inifile);
    GetPrivateProfileStringW(section, L"ProductCode", NULL, packagecode, 100, inifile);
    if (!SdbGUIDFromString(packagecode, &guid))
	{
		printf("Section %ls specifies invalid ProductCode!\n", section);
		fail();
    }

    printf("Writing section %ls\n", section);

    //write MSI_PACKAGE
    TAGID tagid = SdbBeginWriteListTag(pdb, TAG_MSI_PACKAGE);
    SdbWriteStringTag(pdb, TAG_NAME, section);
    SdbWriteStringTag(pdb, TAG_APP_NAME, appname);
    SdbWriteBinaryTag(pdb, TAG_MSI_PACKAGE_ID,(PBYTE) & guid, sizeof(GUID));

    //write MSI_TRANSFORM_REF
    TAGID reftagid = SdbBeginWriteListTag(pdb, TAG_MSI_TRANSFORM_REF);
    SdbWriteStringTag(pdb, TAG_NAME, name);
    SdbWriteDWORDTag(pdb, TAG_MSI_TRANSFORM_TAGID, transfid);
    SdbEndWriteListTag(pdb, reftagid);
    SdbEndWriteListTag(pdb, tagid);

    //write registry
    if (regfile)
	{
		fprintf(regfile, "[HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows NT\\"
				"CurrentVersion\\AppCompatFlags\\Custom\\%ls]\n", packagecode);
		fprintf(regfile, "\"%ls\"=\"%ls\"\n", PathFindFileNameW(sdbfile), appname);
		fprintf(regfile, "\n");
    }
}


void ForEachSection(STRPROC proc)
{
    WCHAR sections[0x10000] = { 0 };
    LPWSTR strW = sections;

    GetPrivateProfileSectionNamesW(strW, 0x10000, inifile);
    for(; *strW; strW += lstrlenW(strW) + 1)
		proc(strW);
}

void CountSection(LPWSTR section)
{
    sections++;
}

void WriteTransforms()
{
    TAGID tagid = SdbBeginWriteListTag(pdb, TAG_LIBRARY);
    ForEachSection(WriteTransform);
    SdbEndWriteListTag(pdb, tagid);
}

void WritePackages()
{
    ForEachSection(WritePackage);
}

void WriteDatabase()
{
    //count number of sections
    sections = 0;
    ForEachSection(CountSection);
    sections = (sections + 15) & ~15;
 
	//create indexes
    INDEXID idx1;
    INDEXID idx2;
    INDEXID idx3;
    SdbDeclareIndex(pdb, TAG_MSI_TRANSFORM, TAG_NAME, sections, TRUE, &idx1);
    SdbDeclareIndex(pdb, TAG_MSI_PACKAGE, TAG_MSI_PACKAGE_ID, sections, FALSE, &idx2);
    SdbDeclareIndex(pdb, TAG_MSI_PACKAGE, TAG_EXE_ID, sections, TRUE, &idx3);
    SdbCommitIndexes(pdb);

    //enable indexing
    SdbStartIndexing(pdb, idx1);
    SdbStartIndexing(pdb, idx2);
    SdbStartIndexing(pdb, idx3);
    
	//create database
    TAGID tagid = SdbBeginWriteListTag(pdb, TAG_DATABASE);
    WriteTransforms();
    WritePackages();
    SdbEndWriteListTag(pdb, tagid);

    //disable indexing
    SdbStopIndexing(pdb, idx1);
    SdbStopIndexing(pdb, idx2);
    SdbStopIndexing(pdb, idx3);
}

int wmain(int argc, WCHAR * argv[])
{
    if (argc != 3 && argc != 4)
	{
		printf("Usage: sdbcreate.exe dbspec.ini out.sdb [out.reg]\n");
		return 1;
    }

    //check ini
    GetFullPathNameW(argv[1], MAX_PATH, inifile, NULL);
    if (GetFileAttributesW(inifile) == INVALID_FILE_ATTRIBUTES)
	{
		printf("Failed to open %ls!\n", inifile);
		return 2;
    }

    //create sdb
    sdbfile = argv[2];
    printf("Creating %ls...\n", sdbfile);
    pdb = SdbCreateDatabase(sdbfile, DOS_PATH);
    if (!pdb)
	{
		printf("Failed to create database!\n");
		return 3;
    }

    //create reg
    regfile = NULL;
    if (argc == 4)
	{
		regfile = _wfopen(argv[3], L"w");
		fprintf(regfile, "REGEDIT4\n\n");
    }

    //write
    WriteDatabase();

    //close
    SdbCloseDatabaseWrite(pdb);
    if (regfile)
		fclose(regfile);

    printf("Finished.");
    return 0;
}
