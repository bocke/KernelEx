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

#ifndef _USER32_APILIST_H
#define _USER32_APILIST_H

#include "auxdecl.h"
#include "kexcoresdk.h"

typedef BOOL (WINAPI *IsHungThread_t)(DWORD ThreadID);
extern IsHungThread_t IsHungThread_pfn;
typedef BOOL (WINAPI *DrawCaptionTempA_t)(HWND, HDC, const RECT*, HFONT, HICON, LPCSTR, UINT);
extern DrawCaptionTempA_t DrawCaptionTempA_pfn;

BOOL init_user32();
extern const apilib_api_table apitable_user32;

/*** AUTOGENERATED APILIST DECLARATIONS BEGIN ***/
LRESULT WINAPI SendMessageA_fix(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
UINT WINAPI MapVirtualKeyA_new(UINT uCode, UINT uMapType);
UINT WINAPI MapVirtualKeyExA_new(UINT uCode, UINT uMapType, HKL dwhkl);
BOOL WINAPI IsHungAppWindow_new(HWND hWnd);
void __stdcall DisableProcessWindowsGhosting_new(void);
BOOL WINAPI EnableWindow_new(HWND hWnd, BOOL bEnable);
HWND APIENTRY GetAncestor_fix(HWND hwnd, UINT gaFlags);
BOOL WINAPI LockWorkStation_new(void);
BOOL WINAPI DrawCaptionTempW_new(HWND hwnd, HDC hdc, const RECT *rect, HFONT hFont, HICON hIcon, LPCWSTR strW, UINT uFlags);
int WINAPI LoadStringW_new(HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int nBufferMax);
UINT WINAPI RealGetWindowClassW_new(HWND hwnd, LPWSTR pszTypeW, UINT cchType);
int WINAPI ToUnicodeEx_new(UINT wVirtKey, UINT wScanCode, const PBYTE lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags, HKL dwhkl);
int WINAPI ToUnicode_new(UINT wVirtKey, UINT wScanCode, const PBYTE lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags);
BOOL WINAPI GetLastInputInfo_new(PLASTINPUTINFO plii);
BOOL WINAPI GetMessageW_new(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
LONG WINAPI GetWindowLongA_new(HWND hWnd, int nIndex);
STUB SetLayeredWindowAttributes_stub;
BOOL WINAPI UpdateLayeredWindow_new(HWND hwnd, HDC hdcDst, POINT *pptDst, SIZE *psize, HDC hdcSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);
LRESULT WINAPI CallWindowProcA_fix(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
/*** AUTOGENERATED APILIST DECLARATIONS END ***/

#endif
