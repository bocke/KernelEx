/*
 *  KernelEx
 *  Copyright (C) 2010, Tihiy, Xeno86
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
#include "k32ord.h"
#include "hwnd9x.h"

static DWORD g_UserBase;
static HTOP_API HWNDtoPWND;

//those are in thunilay
void GrabWin16Lock();
void ReleaseWin16Lock();

#define REBASEUSER(x) ((x) != 0 ? g_UserBase + (DWORD)(x) : 0)

BOOL SetParent_fix_init()
{
	g_UserBase = MapSL(LoadLibrary16("user") << 16);
	/* IsWindow returns PWND */
	HWNDtoPWND = (HTOP_API)IsWindow;
	return (g_UserBase != 0 && HWNDtoPWND != 0);
}

/* returns TRUE if hwnd is a parent of hwndNewParent */
static BOOL TestChild(HWND hwnd, HWND hwndNewParent)
{
	BOOL ret = FALSE;
	PWND pwnd, pwndT;
	GrabWin16Lock();
	pwnd = HWNDtoPWND(hwnd);
	pwndT = HWNDtoPWND(hwndNewParent);
	if ( pwnd && pwndT )
	{
		for ( ; pwndT != NULL; pwndT = (PWND)REBASEUSER(pwndT->spwndParent))
		{
			if (pwnd == pwndT)
			{
				ret = TRUE;
				break;
			}
		}
	}
	ReleaseWin16Lock();	
	return ret;
}

/* MAKE_EXPORT SetParent_new=SetParent */
HWND WINAPI SetParent_new(HWND hWndChild, HWND hWndNewParent)
{
	//forbid changing parent of system windows
	if (IS_SYSTEM_HWND(hWndChild))
	{
		SetLastError(ERROR_ACCESS_DENIED);
		return NULL;
	}
	//test to avoid circular references
	if (TestChild(hWndChild, hWndNewParent))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return NULL;
	}
	return SetParent(hWndChild, hWndNewParent);
}
