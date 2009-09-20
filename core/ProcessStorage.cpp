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

ProcessStorage::ProcessStorage()
{
	InitializeCriticalSection(&cs);
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
	EnterCriticalSection(&cs);

	ret = m_table.get(tag);

	LeaveCriticalSection(&cs);
	return ret;
}

bool ProcessStorage::set(DWORD tag, void* value)
{
	bool ret;
	EnterCriticalSection(&cs);

	if (value == NULL)
	{
		m_table.free(tag);
		ret = true;
	}
	else
	{
		ret = m_table.set(tag, value);
	}

	LeaveCriticalSection(&cs);
	return ret;
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

	pdb->kex_storage = VirtualAlloc(NULL, sizeof(ProcessStorage), 
			MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	DBGASSERT(pdb->kex_storage != NULL);
	ret = new (pdb->kex_storage) ProcessStorage;
	_LeaveSysLevel(krnl32lock);

	return ret;
}
