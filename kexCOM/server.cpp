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

#include <objbase.h>
#include <shlguid.h>
#include "server.h"
#include "factory.h"

long g_LockCount;
HMODULE g_hModule;
LPFNGETCLASSOBJECT SHGetClassObject;


void* operator new(unsigned int n)
{
	return HeapAlloc(GetProcessHeap(), 0, n);
}


void operator delete(void* m)
{
	HeapFree(GetProcessHeap(), 0, m);
}


STDAPI DllCanUnloadNow()
{
	return (g_LockCount > 0) ? S_FALSE : S_OK;
}


STDAPI DllRegisterServer()
{
	LONG result;
	char filename[MAX_PATH];

	GetModuleFileName(g_hModule, filename, sizeof(filename));
	result = RegSetValue(HKEY_CLASSES_ROOT, 
			"CLSID\\{00021401-0000-0000-C000-000000000046}\\InProcServer32", 
			REG_SZ, filename, strlen(filename));

	return (result == ERROR_SUCCESS) ? S_OK : E_FAIL;
}


STDAPI DllUnregisterServer()
{
	LONG result;
	const char szShell32[] = { "shell32.dll" };

	result = RegSetValue(HKEY_CLASSES_ROOT, 
			"CLSID\\{00021401-0000-0000-C000-000000000046}\\InProcServer32", 
			REG_SZ, szShell32, strlen(szShell32));

	return (result == ERROR_SUCCESS) ? S_OK : E_FAIL;
}
		
	
STDAPI DllGetClassObject(const CLSID& clsid, const IID& iid, void** ppv)
{
	HRESULT hr;

	if (clsid == CLSID_ShellLink)
	{
		IClassFactory* pcf;

		hr = SHGetClassObject(CLSID_ShellLink, IID_IClassFactory, (void**) &pcf);
		if (!SUCCEEDED(hr))
			return hr;

		CFactory* factory = new CFactory(pcf);
		if (!factory)
			return E_OUTOFMEMORY;

		hr = factory->QueryInterface(iid, ppv);
		factory->Release();
		return hr;
	}
    else
    {	
        *ppv = NULL;	
        return CLASS_E_CLASSNOTAVAILABLE;
    }
}


BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
    static HMODULE hShell32;

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		g_hModule = hModule;
		DisableThreadLibraryCalls(hModule);

	    hShell32 = LoadLibrary("SHELL32");
		SHGetClassObject = (LPFNGETCLASSOBJECT) GetProcAddress(hShell32, "DllGetClassObject");
	}
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        FreeLibrary(hShell32);
    }

    return TRUE;
}
