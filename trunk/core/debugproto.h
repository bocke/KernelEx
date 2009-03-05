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

#ifndef __DEBUGPROTO_H
#define __DEBUGPROTO_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef KEXCORE_EXPORTS
#define _KEXCOREIMP __declspec(dllexport)
#else
#define _KEXCOREIMP __declspec(dllimport)
#endif


_KEXCOREIMP void kexDbgDumpConfigurations(void);
_KEXCOREIMP void kexDbgDumpImtes(void);
_KEXCOREIMP void kexDbgDumpAppSettings(int flush);


#ifdef __cplusplus
}; /* extern "C" */
#endif


#endif
