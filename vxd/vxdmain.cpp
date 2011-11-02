/*
 *  KernelEx
 *  Copyright (C) 2011, Xeno86
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
extern "C" {
#define WANTVXDWRAPS
#include <vmm.h>
#include <debug.h>
#include <vxdldr.h>
#include <vxdwraps.h>
#include <vwin32.h>
};
#include <winerror.h>
#include "vxdmain.h"
#include "pemanip.h"
#include "patch.h"

_Declare_Virtual_Device(VKRNLEX, 1, 0, ControlDispatcher, UNDEFINED_DEVICE_ID, UNDEFINED_INIT_ORDER, 0, 0, 0);

DWORD ( _stdcall *CVxD_W32_Proc[] )(DWORD, PDIOCPARAMETERS) = {
        VKernelEx_W32_Proc1};

#define MAX_CVXD_W32_API (sizeof(CVxD_W32_Proc)/sizeof(DWORD))

BOOL __stdcall ControlDispatcher(
    DWORD dwControlMessage,
    DWORD EBX,
    DWORD ECX,
    DWORD EDX,
    DWORD ESI,
    DWORD EDI)
{
	switch(dwControlMessage)
	{
	case DEVICE_INIT:
		return VKernelEx_Dynamic_Init();
	case SYS_DYNAMIC_DEVICE_INIT:
		return VKernelEx_Dynamic_Init();
	case SYS_DYNAMIC_DEVICE_EXIT:
		return VKernelEx_Dynamic_Exit();
	case W32_DEVICEIOCONTROL:
		return VKernelEx_W32_DeviceIOControl(ECX, EDX, (PDIOCPARAMETERS) ESI);
	case BEGIN_PM_APP:
		return VKernelEx_Begin_PM_App(EBX);
	case CREATE_PROCESS:
		return VKernelEx_Create_Process(EDX);
	case DESTROY_PROCESS:
		return VKernelEx_Destroy_Process(EDX);
	case SYS_VM_INIT:
	case SYS_VM_TERMINATE:
	case KERNEL32_INITIALIZED:
	case KERNEL32_SHUTDOWN:
		__asm int 3
	default:
		return TRUE;
	}
}

extern "C"
void __cdecl abort(void)
{
	__asm int 3
}

extern "C"
void __cdecl _assert(const char* expr, const char* file, unsigned line)
{
	_Debug_Printf_Service("Assertion failed: '%s' in %s line %d", expr, file, line);
	abort();
}

extern "C"
void __declspec(naked) _stdcall RtlUnwind(
	PVOID TargetFrame,
	PVOID TargetIp,
	PVOID ExceptionRecord,
	PVOID ReturnValue
)
{
	VMMJmp(ObsoleteRtlUnwind);
}

/****************************************************************************
                  VKernelEx_W32_DeviceIOControl
****************************************************************************/
DWORD _stdcall VKernelEx_W32_DeviceIOControl(
	DWORD  dwService,
	DWORD  hDevice,
    PDIOCPARAMETERS lpDIOCParms)
{
    DWORD dwRetVal = 0;

    // DIOC_OPEN is sent when VxD is loaded w/ CreateFile 
    //  (this happens just after SYS_DYNAMIC_INIT)
    if ( dwService == DIOC_OPEN )
    {
        Out_Debug_String("VKRNLEX: WIN32 DEVIOCTL supported here!\n\r");
        // Must return 0 to tell WIN32 that this VxD supports DEVIOCTL
        dwRetVal = 0;
    }
    // DIOC_CLOSEHANDLE is sent when VxD is unloaded w/ CloseHandle
    //  (this happens just before SYS_DYNAMIC_EXIT)
    else if ( dwService == DIOC_CLOSEHANDLE )
    {
        // Dispatch to cleanup proc
        dwRetVal = VKernelEx_CleanUp();
    }
    else if ( dwService > MAX_CVXD_W32_API )
    {
        // Returning a positive value will cause the WIN32 DeviceIOControl
        // call to return FALSE, the error code can then be retrieved
        // via the WIN32 GetLastError
        dwRetVal = ERROR_NOT_SUPPORTED;
    }
    else
    {
        // CALL requested service
        dwRetVal = (CVxD_W32_Proc[dwService-1])(hDevice, lpDIOCParms);
    }
    return dwRetVal;
}

DWORD _stdcall VKernelEx_W32_Proc1(DWORD hDevice, PDIOCPARAMETERS lpDIOCParms)
{
    PDWORD pdw;
	HVM hSysVM;

    Out_Debug_String("VKRNLEX: VKernelEx_W32_Proc1\n\r");

    pdw = (PDWORD)lpDIOCParms->lpvOutBuffer;
    hSysVM = Get_Sys_VM_Handle();
    pdw[0] = hSysVM;
    pdw[1] = Get_Execution_Focus();

    return NO_ERROR;
}

BOOL _stdcall VKernelEx_Create_Process(DWORD pid)
{
	return VXD_SUCCESS;
}

BOOL _stdcall VKernelEx_Destroy_Process(DWORD pid)
{
	return VXD_SUCCESS;
}

BOOL _stdcall VKernelEx_Begin_PM_App(HVM hVM)
{
	WORD version;
	DWORD k32addr;

	if (!Test_Sys_VM_Handle(hVM))
		return FALSE;

	version = Get_VMM_Version();

	if (version >= 0x045A)
		k32addr = 0xBFF60000; //WINME
	else
		k32addr = 0xBFF70000; //WIN98

	__try
	{
		if (*(WORD*)k32addr == 'ZM')
		{
			PEmanip pem((void*) k32addr);
			Patch patch(pem);
			patch.apply();
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		Out_Debug_String("VKRNLEX: Kernel32 fail!\n\r");
		return TRUE;
	}

	Out_Debug_String("VKRNLEX: Kernel32 win!\n\r");
	return TRUE;
}

BOOL _stdcall VKernelEx_Dynamic_Exit(void)
{
    Out_Debug_String("VKRNLEX: Dynamic Exit\n\r");

    return VXD_SUCCESS;
}

DWORD _stdcall VKernelEx_CleanUp(void)
{
    Out_Debug_String("VKRNLEX: Cleaning Up\n\r");
    return VXD_SUCCESS;
}

#pragma VxD_ICODE_SEG
#pragma VxD_IDATA_SEG

BOOL _stdcall VKernelEx_Dynamic_Init(void)
{
    Out_Debug_String("VKRNLEX: Dynamic Init\n\r");

    return VXD_SUCCESS;
}


