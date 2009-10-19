#include <malloc.h>
#include "kexcoresdk.h"

#ifndef __THUNIMACRO_H
#define __THUNIMACRO_H

#ifndef _DEBUG
#define DebugMessage(x) do { } while (0)
#else
#define DebugMessage(x) kexDebugPrint x
#endif

#define MAX_STACK 512

#define HEAP_SIGN 0xCABAC00C
#define STACK_SIGN 0xF00CDEAD

//each day will be DBCS day
#define g_dbcs 2;

/* Tihiy can't get to love Xeno's macros
   and vica versa */

#define STACK_WtoA(strW,strA) \
	strA = (LPSTR)strW; \
	if HIWORD(strW) \
	{ \
		int c = lstrlenW((LPWSTR)strW); \
		c = (c+1)*g_dbcs; \
		strA = (LPSTR)alloca(c); \
		WideCharToMultiByte(CP_ACP, 0, (LPWSTR)strW, -1, (LPSTR)strA, c, NULL, NULL); \
	}
	
#define STACK_AtoW(strA,strW) \
	strW = (LPWSTR)strA; \
	if (HIWORD(strA)) \
	{ \
		int c = lstrlenA((LPSTR)strA); \
		c++; \
		strW = (LPWSTR)alloca(c*sizeof(WCHAR)); \
		MultiByteToWideChar(CP_ACP, 0, (LPSTR)strA, -1, (LPWSTR)strW, c); \
	}

#define BUFFER_ALLOC(BUFTYPE,buffer,len) \
	int size = ((len+1) * 2) + sizeof(DWORD); \
	if (size>MAX_STACK) \
	{\
		buffer = (BUFTYPE)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,size); \
		if ( buffer ) *(DWORD*)buffer = HEAP_SIGN; \
	}\
	else \
	{\
		buffer = (BUFTYPE)alloca( size ); \
		ZeroMemory (buffer, size);  \
		*(DWORD*)buffer = STACK_SIGN; \
	}\
	if ( buffer ) buffer = (BUFTYPE)((DWORD)(buffer) + sizeof(DWORD));
	

#define BUFFER_FREE(buf) \
	if (HIWORD(buf)) \
	{ \
		if ( *(DWORD*)((DWORD)buf - sizeof(DWORD)) == HEAP_SIGN ) HeapFree(GetProcessHeap(),0,buf); \
	}

#define WtoA_len(strW,strA,bufsize) \
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)strW, -1, (LPSTR)strA, bufsize, NULL, NULL);
		
#define AtoW_len(strA,strW,bufsize) \
	MultiByteToWideChar(CP_ACP, 0, (LPSTR)strA, -1, (LPWSTR)strW, bufsize);

#endif
