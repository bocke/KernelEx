/*
 *  KernelEx
 *  Copyright (C) 2008, Xeno86
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

#include <windows.h>

/* MapVirtualKey translation types */
#define MAPVK_VK_TO_VSC     0
#define MAPVK_VSC_TO_VK     1
#define MAPVK_VK_TO_CHAR    2
#define MAPVK_VSC_TO_VK_EX  3
#define MAPVK_VK_TO_VSC_EX  4

/* Scan codes for standard keyboard */
#define VSC_LSHIFT 0x002A
#define VSC_RSHIFT 0x0036
#define VSC_LALT 0x0038
#define VSC_RALT 0xE038
#define VSC_LCONTROL 0x001D
#define VSC_RCONTROL 0xE01D

/*
	From MS keyboard docs:
	Under all Microsoft operating systems, all keyboards actually transmit Scan Code Set 2 values down 
	the wire from the keyboard to the keyboard port. These values are translated to Scan Code Set 1 by 
	the i8042 port chip.
	The rest of the operating system, and all applications that handle scan codes 
	expect the values to be from Scan Code Set 1.
	From other MS docs about USB keyboards:
	The mapper driver translates the Keyboard Page HID usages to PS/2 Set 1 scan codes and forwards them
	to the keyboard class driver.
	Nice link btw: http://www.microsoft.com/taiwan/whdc/archive/w2kbd.mspx

	So we have guarantee AT set (Set 1) will be in scancode.
*/

static inline int NoLeftRightVK(int nVirtKey)
{
	switch(nVirtKey) 
	{
	case VK_LSHIFT:
	case VK_RSHIFT:
		nVirtKey = VK_SHIFT;
		break;
	case VK_LCONTROL:
	case VK_RCONTROL:
		nVirtKey = VK_CONTROL;
		break;
	case VK_LMENU:
	case VK_RMENU:
		nVirtKey = VK_MENU;
		break;
	}
	return nVirtKey;
}

/* MAKE_EXPORT MapVirtualKeyA_new=MapVirtualKeyA */
UINT WINAPI MapVirtualKeyA_new(UINT uCode, UINT uMapType)
{
	switch(uMapType) {
	case MAPVK_VK_TO_VSC_EX:
		if ( uCode == VK_RCONTROL )	return VSC_RCONTROL;
		if ( uCode == VK_RMENU ) return VSC_RALT;
		//fall down
	case MAPVK_VK_TO_VSC:
		if ( uCode == VK_RSHIFT ) return VSC_RSHIFT; //separate scan code
		return MapVirtualKeyA(NoLeftRightVK(uCode),MAPVK_VK_TO_VSC);
	case MAPVK_VSC_TO_VK_EX:		
		switch(uCode) {
		case VSC_RSHIFT:
			return VK_RSHIFT;
		case VSC_LSHIFT:
			return VK_LSHIFT;
		case VSC_LCONTROL:
			return VK_LCONTROL;
		case VSC_RCONTROL:
			return VK_RCONTROL;
		case VSC_LALT:
			return VK_LMENU;
		case VSC_RALT:
			return VK_RMENU;
		default:
			uMapType = MAPVK_VSC_TO_VK;
		}
	}
	return MapVirtualKeyA(uCode,uMapType);
}

/* MAKE_EXPORT MapVirtualKeyExA_new=MapVirtualKeyExA */
UINT WINAPI MapVirtualKeyExA_new(UINT uCode, UINT uMapType, HKL dwhkl)
{
	switch(uMapType) {
	case MAPVK_VK_TO_VSC_EX:
		if ( uCode == VK_RCONTROL )	return VSC_RCONTROL;
		if ( uCode == VK_RMENU ) return VSC_RALT;
		//fall down
	case MAPVK_VK_TO_VSC:
		if ( uCode == VK_RSHIFT ) return VSC_RSHIFT; //separate scan code
		return MapVirtualKeyExA(NoLeftRightVK(uCode),MAPVK_VK_TO_VSC,dwhkl);
	case MAPVK_VSC_TO_VK_EX:		
		switch(uCode) {
		case VSC_RSHIFT:
			return VK_RSHIFT;
		case VSC_LSHIFT:
			return VK_LSHIFT;
		case VSC_LCONTROL:
			return VK_LCONTROL;
		case VSC_RCONTROL:
			return VK_RCONTROL;
		case VSC_LALT:
			return VK_LMENU;
		case VSC_RALT:
			return VK_RMENU;
		default:
			uMapType = MAPVK_VSC_TO_VK;
		}
	}
	return MapVirtualKeyExA(uCode,uMapType,dwhkl);
}
