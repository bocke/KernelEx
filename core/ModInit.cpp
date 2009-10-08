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
#include <stdlib.h>
#include <new>
#include "ModInit.h"
#include "ProcessStorage.h"
#include "internals.h"
#include "debug.h"

static int modinit_index;

bool ModuleInitializer_init()
{
	modinit_index = ProcessStorage::allocate();
	return modinit_index != -1;
}

ModuleInitializer::ModuleInitializer()
{
	size = 0;
	memset(data, 0, sizeof(data));
}

void ModuleInitializer::add_module(MODREF* mr)
{
	data[size++] = mr;
}

bool ModuleInitializer::initialize_modules()
{
	for (int i = 0 ; i < size ; i++)
	{
		DBGPRINTF(("Post-Initializing %s [PID=%08x]\n", 
				(*ppmteModTable)[data[i]->mteIndex]->pszModName, 
				GetCurrentProcessId()));

		if (FLoadTreeNotify(data[i], 1))
			return false;
	}
	return true;
}

ModuleInitializer* ModuleInitializer::get_instance(bool alloc)
{
	ProcessStorage* store = ProcessStorage::get_instance();
	ModuleInitializer* mi = (ModuleInitializer*) store->get(modinit_index);

	if (!mi && alloc)
	{
		mi = (ModuleInitializer*) HeapAlloc(_GetProcessHeap(), 0, sizeof(ModuleInitializer));
		DBGASSERT(mi != NULL);
		new (mi) ModuleInitializer;
		store->set(modinit_index, mi);
	}

	return mi;
}

void ModuleInitializer::destroy()
{
	ProcessStorage* store = ProcessStorage::get_instance();
	HeapFree(_GetProcessHeap(), 0, this);
	store->set(modinit_index, NULL);
}
