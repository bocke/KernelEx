/*
 *  KernelEx
 *  Copyright (C) 2008, Xeno86
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

#include "common.h"
#include "kexcoresdk.h"
#include "_shell32_apilist.h"

BOOL init_shell32()
{
	return TRUE;
}

static const apilib_named_api shell32_named_apis[] = 
{
/*** AUTOGENERATED APILIST NAMED EXPORTS BEGIN ***/
	DECL_API("DragQueryFileW", DragQueryFileW_fwd),
	DECL_API("ExtractIconExW", ExtractIconExW_fwd),
	DECL_API("ExtractIconW", ExtractIconW_fwd),
	DECL_API("FindExecutableW", FindExecutableW_fwd),
	DECL_API("SHBrowseForFolderW", SHBrowseForFolderW_fwd),
	DECL_API("SHFileOperationW", SHFileOperationW_fwd),
	DECL_API("SHGetFileInfoW", SHGetFileInfoW_fwd),
	DECL_API("SHGetFolderLocation", SHGetFolderLocation_new),
	DECL_API("SHGetFolderPathA", SHGetFolderPathA_new),
	DECL_API("SHGetFolderPathW", SHGetFolderPathW_new),
	DECL_API("SHGetNewLinkInfoW", SHGetNewLinkInfoW_fwd),
	DECL_API("SHGetSpecialFolderLocation", SHGetSpecialFolderLocation_fix),
	DECL_API("SHGetSpecialFolderPathA", SHGetSpecialFolderPathA_fix),
	DECL_API("SHGetSpecialFolderPathW", SHGetSpecialFolderPathW_fix),
	DECL_API("SHParseDisplayName", SHParseDisplayName_new),
	DECL_API("ShellAboutW", ShellAboutW_fwd),
	DECL_API("ShellExecuteExW", ShellExecuteExW_fwd),
	DECL_API("ShellExecuteW", ShellExecuteW_fwd),
	DECL_API("Shell_NotifyIconW", Shell_NotifyIconW_fwd),
/*** AUTOGENERATED APILIST NAMED EXPORTS END ***/
};

#if 0
static const apilib_unnamed_api shell32_ordinal_apis[] =
{
/*** AUTOGENERATED APILIST ORDINAL EXPORTS BEGIN ***/
/*** AUTOGENERATED APILIST ORDINAL EXPORTS END ***/
};
#endif

const apilib_api_table apitable_shell32 = DECL_TAB("SHELL32.DLL", shell32_named_apis, 0 /*shell32_ordinal_apis*/);