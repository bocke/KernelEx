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

BOOL init_user32();
extern const apilib_api_table apitable_user32;

/*** AUTOGENERATED APILIST DECLARATIONS BEGIN ***/
FWDPROC AppendMenuW_fwd;
FWDPROC BroadcastSystemMessageW_fwd;
FWDPROC CallWindowProcW_fwd;
FWDPROC ChangeDisplaySettingsExW_fwd;
FWDPROC ChangeDisplaySettingsW_fwd;
FWDPROC ChangeMenuW_fwd;
FWDPROC CreateDialogIndirectParamW_fwd;
FWDPROC CreateMDIWindowW_fwd;
FWDPROC CreateWindowExW_fwd;
FWDPROC DdeCreateStringHandleW_fwd;
FWDPROC DdeInitializeW_fwd;
FWDPROC DdeQueryStringW_fwd;
FWDPROC DefDlgProcW_fwd;
FWDPROC DefFrameProcW_fwd;
FWDPROC DefMDIChildProcW_fwd;
FWDPROC DialogBoxIndirectParamW_fwd;
FWDPROC DialogBoxParamW_fwd;
FWDPROC DlgDirListComboBoxW_fwd;
FWDPROC DlgDirListW_fwd;
FWDPROC DlgDirSelectComboBoxExW_fwd;
FWDPROC DlgDirSelectExW_fwd;
FWDPROC DrawStateW_fwd;
FWDPROC DrawTextExW_fwd;
FWDPROC DrawTextW_fwd;
FWDPROC EnumDisplayDevicesW_fwd;
FWDPROC EnumDisplaySettingsExW_fwd;
FWDPROC EnumDisplaySettingsW_fwd;
FWDPROC EnumPropsExW_fwd;
FWDPROC EnumPropsW_fwd;
FWDPROC FindWindowExW_fwd;
FWDPROC FindWindowW_fwd;
FWDPROC GetAltTabInfoW_fwd;
FWDPROC GetClassInfoExW_fwd;
FWDPROC GetClassInfoW_fwd;
FWDPROC GetClassLongW_fwd;
FWDPROC GetClassNameW_fwd;
FWDPROC GetClipboardFormatNameW_fwd;
FWDPROC GetDlgItemTextW_fwd;
FWDPROC GetKeyboardLayoutNameW_fwd;
FWDPROC GetKeyNameTextW_fwd;
FWDPROC GetMenuItemInfoW_fwd;
FWDPROC GetMenuStringW_fwd;
FWDPROC GetMonitorInfoW_fwd;
FWDPROC GetPropW_fwd;
FWDPROC GetTabbedTextExtentW_fwd;
FWDPROC GetWindowLongW_fwd;
FWDPROC GetWindowTextLengthW_fwd;
FWDPROC GetWindowTextW_fwd;
FWDPROC GrayStringW_fwd;
FWDPROC InsertMenuItemW_fwd;
FWDPROC InsertMenuW_fwd;
FWDPROC IsWindowUnicode_fwd;
FWDPROC LoadAcceleratorsW_fwd;
FWDPROC LoadBitmapW_fwd;
FWDPROC LoadCursorFromFileW_fwd;
FWDPROC LoadCursorW_fwd;
FWDPROC LoadIconW_fwd;
FWDPROC LoadImageW_fwd;
FWDPROC LoadKeyboardLayoutW_fwd;
FWDPROC LoadMenuIndirectW_fwd;
FWDPROC LoadMenuW_fwd;
FWDPROC MapVirtualKeyExW_fwd;
FWDPROC MapVirtualKeyW_fwd;
FWDPROC MessageBoxIndirectW_fwd;
FWDPROC ModifyMenuW_fwd;
FWDPROC PostMessageW_fwd;
FWDPROC PostThreadMessageW_fwd;
FWDPROC RegisterClassExW_fwd;
FWDPROC RegisterClassW_fwd;
FWDPROC RegisterClipboardFormatW_fwd;
FWDPROC RegisterDeviceNotificationW_fwd;
FWDPROC RegisterWindowMessageW_fwd;
FWDPROC RemovePropW_fwd;
FWDPROC SendDlgItemMessageW_fwd;
FWDPROC SendMessageCallbackW_fwd;
FWDPROC SendMessageTimeoutW_fwd;
FWDPROC SendMessageW_fwd;
FWDPROC SendNotifyMessageW_fwd;
FWDPROC SetClassLongW_fwd;
FWDPROC SetDlgItemTextW_fwd;
FWDPROC SetMenuItemInfoW_fwd;
FWDPROC SetPropW_fwd;
FWDPROC SetWindowLongW_fwd;
FWDPROC SetWindowsHookExW_fwd;
FWDPROC SetWindowsHookW_fwd;
FWDPROC SetWindowTextW_fwd;
FWDPROC SystemParametersInfoW_fwd;
FWDPROC TabbedTextOutW_fwd;
FWDPROC UnregisterClassW_fwd;
FWDPROC VkKeyScanExW_fwd;
FWDPROC VkKeyScanW_fwd;
FWDPROC WinHelpW_fwd;
FWDPROC wsprintfW_fwd;
FWDPROC wvsprintfW_fwd;
HWND WINAPI CreateDialogParamW_new(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
LRESULT WINAPI DefWindowProcW_new(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
/*** AUTOGENERATED APILIST DECLARATIONS END ***/

#endif