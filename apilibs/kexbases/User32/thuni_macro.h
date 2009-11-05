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

//In macroses: convert A<->W on stack
#define STACK_WtoA(strW,strA) \
	strA = (LPSTR)strW; \
	if HIWORD(strW) \
	{ \
		int c = lstrlenW((LPWSTR)strW); \
		c = (c+1)*2; \
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

//Out macroses: allocate buffer, call W>-<A function, convert A<->W
#define ABUFFER_ALLOC(buffer,len) \
	int buffer##size = ((len+1) * 2); \
	LPSTR buffer##heap = NULL; \
	if (buffer##size>MAX_STACK) \
	{ \
		buffer##heap = (LPSTR)HeapAlloc(GetProcessHeap(),0,buffer##size); \
		buffer = buffer##heap; \
	} \
	else \
		buffer = (LPSTR)alloca( buffer##size ); \
	*buffer='\0';

#define WBUFFER_ALLOC(buffer,len) \
	int buffer##size = ((len+1) * sizeof(WCHAR)); \
	LPWSTR buffer##heap = NULL; \
	if (buffer##size>MAX_STACK) \
	{ \
		buffer##heap = (LPWSTR)HeapAlloc(GetProcessHeap(),0,buffer##size); \
		buffer = buffer##heap; \
	} \
	else \
		buffer = (LPWSTR)alloca( buffer##size ); \
	*buffer='\0';

#define ABUFFER_toW(bufferA,bufferW,lenW) MultiByteToWideChar(CP_ACP, 0, bufferA, -1, (LPWSTR)bufferW, lenW);
#define WBUFFER_toA(bufferW,bufferA,lenA) WideCharToMultiByte(CP_ACP, 0, bufferW, -1, (LPSTR)bufferA, lenA, NULL, NULL);

#define BUFFER_FREE(buffer) \
	if ( buffer##heap ) HeapFree(GetProcessHeap(),0,buffer##heap); \

#endif
