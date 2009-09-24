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

#include <new>
#include <windows.h>
#include <stdio.h>
#include "apilog.h"
#include "debug.h"
#include "internals.h"
#include "DebugWindow.h"

#define APILOG_TLS_INDEX       78

void* get_process_env_data(const char* env, void* (*creator)())
{
	//environment variable: ENV=ProcessID:DATA
	char buf[20];
	DWORD ret;
	DWORD ProcID;
	void* data = NULL;
	
	ret = GetEnvironmentVariable(env, buf, sizeof(buf));
	if (ret == 0 || ret > sizeof(buf) 
			|| sscanf(buf, "%x:%x", &ProcID, &data) != 2
			|| ProcID != GetCurrentProcessId())
	{
		//invalid/missing value - create new data
		data = creator();
		if (data)
		{
			sprintf(buf, "%x:%x", GetCurrentProcessId(), data);
			SetEnvironmentVariable(env, buf);
		}
	}

	return data;
}

void* heap_creator()
{
	return HeapCreate(0, 0, 0);
}

HANDLE get_process_debug_heap()
{
	return get_process_env_data("KEXDBGH", heap_creator);
}

void* tls_creator()
{
	for (int i = 0 ; i < APILOG_TLS_INDEX+1 ; i++)
		TlsAlloc();
	for (int i = 0 ; i < APILOG_TLS_INDEX ; i++)
		TlsFree(i);
	return (void*) APILOG_TLS_INDEX;
}

DWORD get_process_debug_tls()
{
	return (DWORD) get_process_env_data("KEXDBGT", tls_creator);
}

extern "C"
int snprintf(char *buffer, size_t n, const char* format, ...);

ThreadAddrStack::ThreadAddrStack()
{
	pos = 0;
}

void __stdcall ThreadAddrStack::push_ret_addr(DWORD addr)
{
	ThreadAddrStack* tas = (ThreadAddrStack*) TlsGetValue(APILOG_TLS_INDEX);
	if (!tas)
	{
		void* mem = HeapAlloc(get_process_debug_heap(), 0, sizeof(ThreadAddrStack));
		tas = new (mem) ThreadAddrStack;
		TlsSetValue(APILOG_TLS_INDEX, mem);
	}
	tas->stack[tas->pos++] = addr;
	DBGASSERT(tas->pos < sizeof(tas->stack) / sizeof(tas->stack[0]));
}

DWORD __stdcall ThreadAddrStack::pop_ret_addr()
{
	ThreadAddrStack* tas = (ThreadAddrStack*) TlsGetValue(APILOG_TLS_INDEX);
	DBGASSERT(tas->pos > 0);
	return tas->stack[--tas->pos];
}

DWORD __stdcall ThreadAddrStack::get_level()
{
	ThreadAddrStack* tas = (ThreadAddrStack*) TlsGetValue(APILOG_TLS_INDEX);
	return tas->pos;
}


log_stub::log_stub(const char* source, const char* target, const char* name, 
		unsigned long proc)
		: call_prelog(DWORD(pre_log)), call_postlog(DWORD(post_log)),
		call_orig(proc)
{
	c_pushad1 = c_pushad2 = 0x60;
	c_popad1 = c_popad2 = 0x61;
	c_ret = 0xc3;
	c_push1 = c_push2 = 0x68;
	v_lgd1 = &lgd;
	v_lgd2 = &lgd;
	c_push_eax = 0x50;
	c_add_esp = 0xc483;
	c_sub_esp = 0xec83;
	c_byte_4 = c_byte_4_1 = 4;
	lgd.source = source;
	lgd.target = target;
	lgd.api_name = name;
}

void __stdcall log_stub::pre_log(log_data* lgd)
{
	DWORD last_err;
	DWORD caller_addr;
	DWORD level;
	char msg[DEBUGMSG_MAXLEN];
	
	caller_addr = *((DWORD*) &lgd + 9);
	last_err = GetLastError();
	
	ThreadAddrStack::push_ret_addr(caller_addr);
	
	DebugWindow* dw = DebugWindow::get();
	if (!dw)
		return;

	level = ThreadAddrStack::get_level();

	snprintf(msg, sizeof(msg), "%-2d|%x|%*s[%s]%08x:<%s>%s", 
			level,
			GetCurrentThreadId(),
			(level-1) * 2, "",
			lgd->source, caller_addr,
			lgd->target, lgd->api_name);

	dw->append(msg);

	SetLastError(last_err);
}

void __stdcall log_stub::post_log(log_data* lgd, DWORD retval)
{
	DWORD last_err;
	DWORD& caller_addr = *((DWORD*) &retval + 9);
	DWORD level;
	char msg[DEBUGMSG_MAXLEN];
	
	last_err = GetLastError();
	
	DebugWindow* dw = DebugWindow::get();
	if (!dw)
		return;

	level = ThreadAddrStack::get_level();

	caller_addr = ThreadAddrStack::pop_ret_addr();

	snprintf(msg, sizeof(msg), "%-2d|%x|%*s[%s]%08x:<%s>%s|%x", 
			level,
			GetCurrentThreadId(),
			(level-1) * 2, "",
			lgd->source, caller_addr,
			lgd->target, lgd->api_name,
			retval);

	dw->append(msg);

	SetLastError(last_err);
}

PROC create_log_stub(const char* caller, const char* target, const char* api, PROC orig)
{
	HANDLE heap = get_process_debug_heap();
	char* new_api = (char*) HeapAlloc(heap, 0, strlen(api) + 1);
	strcpy(new_api, api);
	get_process_debug_tls();
	void* mem = HeapAlloc(heap, 0, sizeof(log_stub));
	return (PROC) new (mem) log_stub(caller, 
			target, new_api, (unsigned long) orig);
}

PROC create_log_stub(const char* caller, const char* target, WORD ord, PROC orig)
{
	char ord_name[16];
	snprintf(ord_name, sizeof(ord_name), "Ordinal:%d", ord);
	return create_log_stub(caller, target, ord_name, orig);
}
