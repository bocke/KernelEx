/*
 *  KernelEx
 *  Copyright (C) 2009, Xeno86
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
#include "unifwd.h"
#include "kexcoresdk.h"
#include "comdlg32/_comdlg32_apilist.h"
#include "shell32/_shell32_apilist.h"
//#include "/__apilist.h"

static apilib_api_table api_table[3];

static void fill_apitable()
{
	api_table[0] = apitable_comdlg32;
	api_table[1] = apitable_shell32;
	//last entry is null terminator
}

extern "C"
__declspec(dllexport)
const apilib_api_table* get_api_table()
{
	fill_apitable();
	return api_table;
}

BOOL init()
{
	//force reference comdlg32 - this is never called, only to force import
	if (!&api_table) ChooseColorA(0);
		
	return common_init() && init_comdlg32() && init_shell32();
}

BOOL APIENTRY DllMain(HINSTANCE instance, DWORD reason, BOOL load_static)
{
	switch (reason) 
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(instance);
		if (!init())
			return FALSE;
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
