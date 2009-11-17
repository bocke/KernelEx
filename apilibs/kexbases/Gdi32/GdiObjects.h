/*
 *  KernelEx
 *
 *  Copyright (C) 2009, Tihiy
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

#ifndef __GDI9X_H
#define __GDI9X_H

//those are in thunilay
void GrabWin16Lock();
void ReleaseWin16Lock();

#define LHE_DISCARDED	0x40
#define LHE_MUTATED		0x80
#define LHE_FREEHANDLE	0xFF

#define GDI_TYPEMASK	0x5FFF
#define GDI_TYPE_PEN	0x4F47
#define GDI_TYPE_BRUSH	0x4F48
#define GDI_TYPE_FONT	0x4F49
#define GDI_TYPE_PAL	0x4F4A
#define GDI_TYPE_BITMAP	0x4F4B
#define GDI_TYPE_REGION	0x4F4C
#define GDI_TYPE_DC		0x4F4D
#define GDI_TYPE_DCX	0x4F4E
#define GDI_TYPE_DCY	0x4F4F
#define GDI_TYPE_METADC	0x4F51
#define GDI_TYPE_ENHMETA 0x4F52

#define SEL_FONT_ONCE	0x4
#define SEL_FONT_DEL	0x2
#define SEL_BITMAP_ONCE	0x01
#define SEL_BITMAP_DEL	0x10

#define ResetMapMode( hdc ) SetMapMode( hdc, GetMapMode(hdc) )

#pragma pack(push,1)

typedef struct
{
	WORD bDoesntExist;
	DWORD dwOldSSSP;
    WORD pLocalHeap;
    WORD pAtomTable;
    WORD pStackTop;
    WORD pStackMin;
    WORD pStackBottom;
} INSTANCE16, *PINSTANCE16;

typedef struct
{
	WORD wBlock;
	BYTE bFlags;
	BYTE bLocks;
} LHENTRY, *PLHENTRY;

typedef struct
{
	WORD wZero;				//+0
	WORD wType;				//+2
	DWORD dwNumber;			//+4
	DWORD dwSpecific;		//+8
	WORD wOwner;			//+C
} GDIOBJ16, *PGDIOBJ16;

typedef struct
{
	GDIOBJ16 header;
	WORD wGlobalBitmap;		//+14
	WORD wSelCount;			//+16
	WORD wHDC;				//+18
	WORD wGlobalBitmapInfo;	//+20
	DWORD dwReservedShit;	//+22
	WORD wBitmapStuff;		//+26
	WORD wDeviceStuff;		//+28
	WORD wBitmapType;		//+30
	WORD wLogColorSpace;	//+32
} BITMAPOBJ16, *PBITMAPOBJ16;

typedef struct
{
	WORD wZero;				//+0
	WORD wType;				//+2
	DWORD dwStuff;			//+4
	WORD wReserved;			//+8 (not used?)
	WORD wSelCount;			//+A 
	WORD wOwner;			//+C
} FONTOBJ16, *PFONTOBJ16;

typedef struct
{
	WORD wZero;				//+0
	WORD wType;				//+2
	DWORD dwNumber;			//+4
	DWORD dwBrushStuff;		//+8
	WORD wOwner;			//+C
	DWORD dcFlags;			//+E
	DWORD stuff[3];			//+12
	WORD wBitmapHandle;		//+1E
	DWORD stuff2[4];		//+20
	WORD dummy2;			//+30	
	WORD wGlobalBitmapSelector; //+32
	WORD dummy;				//+34
	WORD wGlobalBitmap;		//+36
	BYTE skip1[0x4C];		//+38
	WORD WindowExtX;		//+84
	WORD WindowExtY;		//+86
	BYTE filler2[4];		//+88
	WORD ViewportExtX;		//+8C
	WORD ViewportExtY;		//+8E
	BYTE filler3[4];		//+90
	WORD mapmode;			//+94
	BYTE filler4[0x68];		//+96
	DWORD lockFlags;		//+FE
	DWORD skip2;			//+102	
	WORD enhmetadc;			//+106
} DCOBJ, *PDCOBJ;

#pragma pack(pop)

PGDIOBJ16 GetGDIObjectPtr( HGDIOBJ hgdiobj );
#define GetDCObj(x) (PDCOBJ)GetGDIObjectPtr(x)

#endif
