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

#include <windows.h>
#include <new>
#include "ProcessStorage.h"
#include "internals.h"
#include "debug.h"

struct PDB_KEX : PDB98
{
	void* kex_storage;
};

ProcessStorage::ProcessStorage(HANDLE heap) 
	: m_allocator(heap), m_table(std::less<DWORD>(), m_allocator)
{
	InitializeCriticalSection(&m_cs);
}

ProcessStorage* ProcessStorage::get_instance()
{
	PDB_KEX* pdb = (PDB_KEX*) *pppdbCur;
	if (!pdb->kex_storage)
		return create_instance();
	return (ProcessStorage*) pdb->kex_storage;
}

void* ProcessStorage::get(DWORD tag)
{
	void* ret;
	_Map::iterator it;
	
	EnterCriticalSection(&m_cs);

	it = m_table.find(tag);
	if (it != m_table.end())
		ret = it->second;
	else
		ret = NULL;

	LeaveCriticalSection(&m_cs);

	return ret;
}

bool ProcessStorage::set(DWORD tag, void* value)
{
	bool ret;
	_Map::iterator it;

	EnterCriticalSection(&m_cs);

	if (value == NULL)
	{
		m_table.erase(tag);
		ret = true;
	}
	else
	{
		it = m_table.lower_bound(tag);
		if (it == m_table.end() || m_table.key_comp()(tag, it->first))
			m_table.insert(it, std::pair<DWORD,void*>(tag, value));
		else
			it->second = value;
		ret = true;
	}

	LeaveCriticalSection(&m_cs);

	return ret;
}

void* ProcessStorage::allocate(int n)
{
	return _Allocator::rebind<char>::other(m_allocator).allocate(n, (char*) 0);
}

void ProcessStorage::deallocate(void* ptr)
{
	_Allocator::rebind<char>::other(m_allocator).deallocate(ptr, 0);
}


ProcessStorage* ProcessStorage::create_instance()
{
	ProcessStorage* ret;
	PDB_KEX* pdb = (PDB_KEX*) *pppdbCur;

	_EnterSysLevel(krnl32lock);
	//double check - we might have been waiting on krnl32lock for create_instance
	if (pdb->kex_storage)
	{
		_LeaveSysLevel(krnl32lock);
		return (ProcessStorage*) pdb->kex_storage;
	}

	HANDLE heap = HeapCreate(0, 0, 0);
	DBGASSERT(heap != NULL);

	pdb->kex_storage = HeapAlloc(heap, 0, sizeof(ProcessStorage));
	DBGASSERT(pdb->kex_storage != NULL);
	
	ret = new (pdb->kex_storage) ProcessStorage(heap);
	_LeaveSysLevel(krnl32lock);

	return ret;
}
