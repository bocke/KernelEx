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
#include "_advapi32_apilist.h"

BOOL init_advapi32()
{
	return TRUE;
}

static const apilib_named_api advapi32_named_apis[] = 
{
/*** AUTOGENERATED APILIST NAMED EXPORTS BEGIN ***/
	DECL_API("GetUserNameW", GetUserNameW_fwd),
	DECL_API("IsTextUnicode", IsTextUnicode_fwd),
	DECL_API("RegConnectRegistryW", RegConnectRegistryW_fwd),
	DECL_API("RegCreateKeyExW", RegCreateKeyExW_fwd),
	DECL_API("RegCreateKeyW", RegCreateKeyW_fwd),
	DECL_API("RegDeleteKeyW", RegDeleteKeyW_fwd),
	DECL_API("RegDeleteValueW", RegDeleteValueW_fwd),
	DECL_API("RegEnumKeyExW", RegEnumKeyExW_fwd),
	DECL_API("RegEnumKeyW", RegEnumKeyW_fwd),
	DECL_API("RegLoadKeyW", RegLoadKeyW_fwd),
	DECL_API("RegOpenKeyExW", RegOpenKeyExW_fwd),
	DECL_API("RegOpenKeyW", RegOpenKeyW_fwd),
	DECL_API("RegQueryInfoKeyW", RegQueryInfoKeyW_fwd),
	DECL_API("RegQueryMultipleValuesW", RegQueryMultipleValuesW_fwd),
	DECL_API("RegQueryValueW", RegQueryValueW_fwd),
	DECL_API("RegReplaceKeyW", RegReplaceKeyW_fwd),
	DECL_API("RegSaveKeyW", RegSaveKeyW_fwd),
	DECL_API("RegSetValueExW", RegSetValueExW_fwd),
	DECL_API("RegSetValueW", RegSetValueW_fwd),
	DECL_API("RegUnLoadKeyW", RegUnLoadKeyW_fwd),
/*** AUTOGENERATED APILIST NAMED EXPORTS END ***/
};

#if 0
static const apilib_unnamed_api advapi32_ordinal_apis[] =
{
/*** AUTOGENERATED APILIST ORDINAL EXPORTS BEGIN ***/
/*** AUTOGENERATED APILIST ORDINAL EXPORTS END ***/
};
#endif

const apilib_api_table apitable_advapi32 = DECL_TAB("ADVAPI32.DLL", advapi32_named_apis, 0 /*advapi32_ordinal_apis*/);
