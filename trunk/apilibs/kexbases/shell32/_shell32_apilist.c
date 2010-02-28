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
#include "../kernel32/_kernel32_apilist.h"

BOOL init_shell32()
{
	return TRUE;
}

/*
 * MAKE_EXPORT GetDiskFreeSpaceExA_fix=SHGetDiskFreeSpaceA
 * MAKE_EXPORT GetDiskFreeSpaceExW_new=SHGetDiskFreeSpaceW
 * MAKE_EXPORT GetDiskFreeSpaceExA_fix=SHGetDiskFreeSpaceExA
 * MAKE_EXPORT GetDiskFreeSpaceExW_new=SHGetDiskFreeSpaceExW
 */

static const apilib_named_api shell32_named_apis[] = 
{
/*** AUTOGENERATED APILIST NAMED EXPORTS BEGIN ***/
	DECL_API("CommandLineToArgvW", CommandLineToArgvW_new),
	DECL_API("IsUserAnAdmin", IsUserAnAdmin_new),
	DECL_API("SHCreateShellItem", SHCreateShellItem_stub),
	DECL_API("SHGetDiskFreeSpaceA", GetDiskFreeSpaceExA_fix),
	DECL_API("SHGetDiskFreeSpaceExA", GetDiskFreeSpaceExA_fix),
	DECL_API("SHGetDiskFreeSpaceExW", GetDiskFreeSpaceExW_new),
	DECL_API("SHGetDiskFreeSpaceW", GetDiskFreeSpaceExW_new),
	DECL_API("SHOpenFolderAndSelectItems", SHOpenFolderAndSelectItems_stub),
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
