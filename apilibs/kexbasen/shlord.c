/*
 *  KernelEx
 *  Copyright (C) 2009, Tihiy
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
#include "shlord.h"
#include "common.h"

static HMODULE hShlwapi;

void shlwapi_fatal_error(int funcnum)
{
	char msg[256];
	sprintf(msg, "kexbasen: Failed to get shlwapi proc: #%i",funcnum);	
	fatal_error(msg);
}

PVOID WINAPI GetShlwapiProc(int funcnum)
{
	if (!hShlwapi) 
	{
		hShlwapi = GetModuleHandle("shlwapi.dll");
		if (!hShlwapi)
			hShlwapi = LoadLibrary("shlwapi.dll");
	}
	PVOID proc = GetProcAddress(hShlwapi,(LPSTR)funcnum);
	if (!proc)
		shlwapi_fatal_error(funcnum);
	return proc;	
}
