/*
 *  KernelEx
 *  Copyright (C) 2009 Tihiy
 *	Copyright (C) 1999 George Marsaglia
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

#define UL unsigned long
#define znew  ((z=36969*(z&65535)+(z>>16))<<16)
#define wnew  ((w=18000*(w&65535)+(w>>16))&65535)
#define MWC   (znew+wnew)
#define SHR3  (jsr=(jsr=(jsr=jsr^(jsr<<17))^(jsr>>13))^(jsr<<5))
#define CONG  (jcong=69069*jcong+1234567)
#define KISS  ((MWC^CONG)+SHR3)
#define LFIB4 (t[c]=t[c]+t[c+58]+t[c+119]+t[++c+178])
#define SWB   (t[c+237]=(x=t[c+15])-(y=t[++c]+(x<y)))
#define UNI   (KISS*2.328306e-10)
#define VNI   ((long) KISS)*4.656613e-10
/*  Global static variables: */
 static UL z=362436069, w=521288629, jsr=123456789, jcong=380116160;
 static UL t[256];
 static UL x=0,y=0; static unsigned char c=0;

/* Random seeds must be used to reset z,w,jsr,jcong and
the table t[256]  Here is an example procedure, using KISS: */

void settable(UL i1,UL i2,UL i3,UL i4)
{
	int i; z=i1;w=i2,jsr=i3; jcong=i4;
	for(i=0;i<256;i++)  t[i]=KISS;
}

/* MAKE_EXPORT SystemFunction036_new=SystemFunction036 */
BOOL WINAPI SystemFunction036_new(PVOID pbBuffer, ULONG dwLen)
{
	static BOOL bInit = FALSE;
	ULONG i;
	PUCHAR cBuffer = (PUCHAR) pbBuffer;

	if (!pbBuffer || !dwLen)
		return FALSE;
	if (!bInit) //init once
	{
		settable(GetTickCount(),GetCurrentThreadId(),GetCurrentProcessId(),GetSysColor(COLOR_BACKGROUND));
		bInit = TRUE;
	}
	for (i=0;i<dwLen;i++)
	{
		*cBuffer = SWB;
		cBuffer++;
	}
	return TRUE;
}
