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

#ifndef __PROCESSSTORAGE_H
#define __PROCESSSTORAGE_H

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <map>
#include "winheap_allocator.hpp"

#define MAKE_PS_TAG(a,b,c,d)     (d<<24 | c<<16 | b<<8 | a)

class ProcessStorage
{
public:
	static ProcessStorage* get_instance();
	void* get(DWORD tag);
	bool set(DWORD tag, void* value);
	void* allocate(int n);
	void deallocate(void* ptr);

private:
	typedef winheap_allocator<std::pair<DWORD,void*> > _Allocator;
	typedef std::map<DWORD, void*, std::less<DWORD>, _Allocator> _Map;
	_Allocator m_allocator;
	_Map m_table;
	CRITICAL_SECTION m_cs;

	static ProcessStorage* create_instance();
	ProcessStorage(HANDLE heap);
	~ProcessStorage();
};

#endif
