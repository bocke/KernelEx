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

#ifndef __APILOG_H
#define __APILOG_H

#include "resolver.h"


class ThreadAddrStack
{
public:
	ThreadAddrStack();
	static void __stdcall push_ret_addr(DWORD tls, DWORD addr);
	static DWORD __stdcall pop_ret_addr(DWORD tls);

private:
	int pos;
	DWORD stack[1023];
};

#pragma pack(push,1)

/* Creates a stub for api logging. */
class log_stub
{
public:
	log_stub(const char* source, const char* target, const char* name, 
			unsigned long proc, unsigned long log_fun, DWORD tls) 
			: call_orig(proc, true), jmp_logfun(log_fun), 
			tas_store((unsigned long) ThreadAddrStack::push_ret_addr, true),
			tas_restore((unsigned long) ThreadAddrStack::pop_ret_addr, true)
	{
		c_push1 = c_push2 = c_push3 = c_push4 = c_push5 = 0x68;
		tls1 = tls2 = tls;
		v_source = source;
		v_target = target;
		v_name = name;
		c_pusheax1 = c_pusheax2 = 0x50;
	}

private:
	unsigned char c_push1;
	DWORD tls1;
	redir_stub tas_store;     //arg1=tls, arg2=caller ret
	redir_stub call_orig;
	unsigned char c_pusheax1; //orig ret
	unsigned char c_push2;    //api name
	const char* v_name;
	unsigned char c_push3;    //target module
	const char* v_target;
	unsigned char c_push4;    //calling module
	const char* v_source;
	unsigned char c_push5;    //tls
	DWORD tls2;
	redir_stub tas_restore;
	unsigned char c_pusheax2; //caller return address	
	redir_stub jmp_logfun;    //jump to log_fun
};

#pragma pack(pop)

PROC create_log_stub(const char* caller, const char* target, const char* api, PROC orig);


#endif
