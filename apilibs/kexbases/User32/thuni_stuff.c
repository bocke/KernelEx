/*
 *  KernelEx
 *
 *  Copyright (C) 2010, Tihiy
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

/* various thuni routines here */

#include <windows.h>
#include "thuni_layer.h"

static LPCRITICAL_SECTION pWin16Mutex;
DWORD g_UserBase;
HMODULE g_hUser32;

BOOL InitUniThunkLayerStuff()
{
	_GetpWin16Lock( &pWin16Mutex );
	g_UserBase = MapSL(LoadLibrary16("user") << 16);
	g_hUser32 = GetModuleHandleA("user32");	

	return (g_UserBase && g_hUser32);
}

void GrabWin16Lock()
{
	_EnterSysLevel(pWin16Mutex);
}

void ReleaseWin16Lock()
{
	_LeaveSysLevel(pWin16Mutex);
}

DWORD GetWindowProcessId( HWND hwnd )
{
	DWORD procID = 0;
	GetWindowThreadProcessId( hwnd, &procID );
	return procID;
}

__declspec(naked)
LRESULT WINAPI CallWindowProc_stdcall( WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
__asm {
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 12
	push [ebp+24]
	push [ebp+20]
	push [ebp+16]
	push [ebp+12]
	mov eax, [ebp+8]
	call eax
	lea esp, [ebp-12]
	pop ebx
	pop esi
	pop edi
	leave
	ret 20
	}	
}

int GetCPFromLocale(LCID Locale)
{
	int cp;	
	Locale = LOWORD(Locale);
	if (GetLocaleInfoA(Locale,LOCALE_IDEFAULTANSICODEPAGE | LOCALE_RETURN_NUMBER,(LPSTR)&cp,sizeof(int)))
		return cp;
	else
		return CP_ACP;
}

UINT GetCurrentKeyboardCP()
{
	return GetCPFromLocale((LCID)GetKeyboardLayout(0));
}

#pragma warning (disable:4035)
static inline
WORD GetCurrentThreadhQueue() 
{
	__asm mov ax, fs:[28h]
}
#pragma warning (default:4035)

PMSGQUEUE GetCurrentThreadQueue()
{
	return (PMSGQUEUE)MapSL( GetCurrentThreadhQueue() << 16 );
}

