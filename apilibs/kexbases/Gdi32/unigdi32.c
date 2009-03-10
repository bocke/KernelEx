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
#include "_gdi32_apilist.h"

//MAKE_EXPORT AddFontResourceExW_new=AddFontResourceExW
INT WINAPI AddFontResourceExW_new(LPCWSTR strW, DWORD fl, PVOID pdv)
{
	file_GetCP();
	file_ALLOC_WtoA(str);
	return AddFontResourceExA_new(strA, fl, pdv);
}

//MAKE_EXPORT AddFontResourceW_new=AddFontResourceW
INT WINAPI AddFontResourceW_new(LPCWSTR strW)
{
	file_GetCP();
	file_ALLOC_WtoA(str);
	return AddFontResourceA(strA);
}

//MAKE_EXPORT RemoveFontResourceExW_new=RemoveFontResourceExW
BOOL WINAPI RemoveFontResourceExW_new(LPCWSTR strW, DWORD fl, PVOID pdv)
{
	file_GetCP();
	file_ALLOC_WtoA(str);
	return RemoveFontResourceExA_new(strA, fl, pdv);
}

//MAKE_EXPORT RemoveFontResourceW_new=RemoveFontResourceW
BOOL WINAPI RemoveFontResourceW_new(LPCWSTR strW)
{
	file_GetCP();
	file_ALLOC_WtoA(str);
	return RemoveFontResourceA(strA);
}
