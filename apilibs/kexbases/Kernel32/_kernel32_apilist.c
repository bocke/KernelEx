/*
 *  KernelEx
 *  Copyright (C) 2008, Xeno86
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

/*TODOS:
CreateRemoteThread
http://17slon.com/blogs/gabr/2007/02/four-ways-to-detect-vista.html
*/

#include "common.h"
#include "kexcoresdk.h"
#include "_kernel32_apilist.h"

void get_cpuinfo();
BOOL init_tryentercritsec();

BOOL init_kernel32()
{
	get_cpuinfo();
	return init_tryentercritsec();
}

/*
 * MAKE_EXPORT GetWindowsDirectoryA=GetSystemWindowsDirectoryA
 * MAKE_EXPORT GetWindowsDirectoryW_new=GetSystemWindowsDirectoryW
 * MAKE_EXPORT GetSystemInfo=GetNativeSystemInfo
 * MAKE_EXPORT SetLastError=RestoreLastError
 */

static const apilib_named_api kernel32_named_apis[] = 
{
/*** AUTOGENERATED APILIST NAMED EXPORTS BEGIN ***/
	DECL_API("AddAtomW", AddAtomW_new),
	DECL_API("AssignProcessToJobObject", AssignProcessToJobObject_new),
	DECL_API("CompareStringW", CompareStringW_new),
	DECL_API("CopyFileExA", CopyFileExA_new),
	DECL_API("CopyFileExW", CopyFileExW_new),
	DECL_API("CopyFileW", CopyFileW_new),
	DECL_API("CreateDirectoryExW", CreateDirectoryExW_new),
	DECL_API("CreateDirectoryW", CreateDirectoryW_new),
	DECL_API("CreateFiberEx", CreateFiberEx_new),
	DECL_API("CreateFileA", CreateFileA_fix),
	DECL_API("CreateFileW", CreateFileW_new),
	DECL_API("CreateHardLinkA", CreateHardLinkA_stub),
	DECL_API("CreateHardLinkW", CreateHardLinkW_stub),
	DECL_API("CreateIoCompletionPort", CreateIoCompletionPort_new),
	DECL_API("CreateJobObjectA", CreateJobObjectA_new),
	DECL_API("CreateJobObjectW", CreateJobObjectW_new),
	DECL_API("CreateThread", CreateThread_fix),
	DECL_API("DecodePointer", XorPointer),
	DECL_API("DecodeSystemPointer", XorPointer),
	DECL_API("DefineDosDeviceW", DefineDosDeviceW_new),
	DECL_API("DeleteCriticalSection", DeleteCriticalSection_fix),
	DECL_API("DeleteFileW", DeleteFileW_new),
	DECL_API("EncodePointer", XorPointer),
	DECL_API("EncodeSystemPointer", XorPointer),
	DECL_API("EnterCriticalSection", EnterCriticalSection_fix),
	DECL_API("EnumUILanguagesA", EnumUILanguagesA_new),
	DECL_API("EnumUILanguagesW", EnumUILanguagesW_new),
	DECL_API("ExitProcess", ExitProcess_fix),
	DECL_API("FindAtomW", FindAtomW_new),
	DECL_API("FindFirstChangeNotificationW", FindFirstChangeNotificationW_new),
	DECL_API("FindFirstFileExA", FindFirstFileExA_new),
	DECL_API("FindFirstFileExW", FindFirstFileExW_new),
	DECL_API("FindFirstFileW", FindFirstFileW_new),
	DECL_API("FindNextFileW", FindNextFileW_new),
	DECL_API("FindResourceExW", FindResourceExW_new),
	DECL_API("FindResourceW", FindResourceW_new),
	DECL_API("FoldStringA", FoldStringA_new),
	DECL_API("FoldStringW", FoldStringW_new),
	DECL_API("FreeEnvironmentStringsW", FreeEnvironmentStringsW_new),
	DECL_API("GetAtomNameW", GetAtomNameW_new),
	DECL_API("GetComputerNameExA", GetComputerNameExA_stub),
	DECL_API("GetComputerNameExW", GetComputerNameExW_stub),
	DECL_API("GetConsoleWindow", GetConsoleWindow_new),
	DECL_API("GetCurrentDirectoryW", GetCurrentDirectoryW_new),
	DECL_API("GetDefaultCommConfigW", GetDefaultCommConfigW_new),
	DECL_API("GetDiskFreeSpaceA", GetDiskFreeSpaceA_fix),
	DECL_API("GetDiskFreeSpaceExA", GetDiskFreeSpaceExA_fix),
	DECL_API("GetDiskFreeSpaceExW", GetDiskFreeSpaceExW_new),
	DECL_API("GetDiskFreeSpaceW", GetDiskFreeSpaceW_new),
	DECL_API("GetEnvironmentStringsW", GetEnvironmentStringsW_new),
	DECL_API("GetFileAttributesExW", GetFileAttributesExW_new),
	DECL_API("GetFileAttributesW", GetFileAttributesW_new),
	DECL_API("GetFileSizeEx", GetFileSizeEx_new),
	DECL_API("GetFullPathNameW", GetFullPathNameW_new),
	DECL_API("GetLocaleInfoW", GetLocaleInfoW_new),
	DECL_API("GetLongPathNameW", GetLongPathNameW_new),
	DECL_API("GetModuleFileNameW", GetModuleFileNameW_new),
	DECL_API("GetModuleHandleExA", GetModuleHandleExA_new),
	DECL_API("GetModuleHandleExW", GetModuleHandleExW_new),
	DECL_API("GetModuleHandleW", GetModuleHandleW_new),
	DECL_API("GetNativeSystemInfo", GetSystemInfo),
	DECL_API("GetProcessId", GetProcessId_new),
	DECL_API("GetProcessIoCounters", GetProcessIoCounters_stub),
	DECL_API("GetQueuedCompletionStatus", GetQueuedCompletionStatus_new),
	DECL_API("GetShortPathNameW", GetShortPathNameW_new),
	DECL_API("GetStartupInfoW", GetStartupInfoW_new),
	DECL_API("GetStringTypeExW", GetStringTypeExW_new),
	DECL_API("GetStringTypeW", GetStringTypeW_new),
	DECL_API("GetSystemDefaultUILanguage", GetSystemDefaultUILanguage_new),
	DECL_API("GetSystemDirectoryW", GetSystemDirectoryW_new),
	DECL_API("GetSystemWindowsDirectoryA", GetWindowsDirectoryA),
	DECL_API("GetSystemWindowsDirectoryW", GetWindowsDirectoryW_new),
	DECL_API("GetTempFileNameA", GetTempFileNameA_fix),
	DECL_API("GetTempFileNameW", GetTempFileNameW_new),
	DECL_API("GetTempPathW", GetTempPathW_new),
	DECL_API("GetUserDefaultUILanguage", GetUserDefaultUILanguage_new),
	DECL_API("GetVersion", GetVersion_WIN95),
	DECL_API("GetVersion", GetVersion_WIN98),
	DECL_API("GetVersion", GetVersion_WINME),
	DECL_API("GetVersion", GetVersion_NT40),
	DECL_API("GetVersion", GetVersion_NT2K),
	DECL_API("GetVersion", GetVersion_WINXP),
	DECL_API("GetVersion", GetVersion_WIN2K3),
	DECL_API("GetVersion", GetVersion_VISTA),
	DECL_API("GetVersion", GetVersion_WIN2K8),
	DECL_API("GetVersionExA", GetVersionExA_ORIG),
	DECL_API("GetVersionExA", GetVersionExA_WIN95),
	DECL_API("GetVersionExA", GetVersionExA_WIN98),
	DECL_API("GetVersionExA", GetVersionExA_WINME),
	DECL_API("GetVersionExA", GetVersionExA_NT40),
	DECL_API("GetVersionExA", GetVersionExA_NT2K),
	DECL_API("GetVersionExA", GetVersionExA_WINXP),
	DECL_API("GetVersionExA", GetVersionExA_WIN2K3),
	DECL_API("GetVersionExA", GetVersionExA_VISTA),
	DECL_API("GetVersionExA", GetVersionExA_WIN2K8),
	DECL_API("GetVersionExW", GetVersionExW_ORIG),
	DECL_API("GetVersionExW", GetVersionExW_WIN95),
	DECL_API("GetVersionExW", GetVersionExW_WIN98),
	DECL_API("GetVersionExW", GetVersionExW_WINME),
	DECL_API("GetVersionExW", GetVersionExW_NT40),
	DECL_API("GetVersionExW", GetVersionExW_NT2K),
	DECL_API("GetVersionExW", GetVersionExW_WINXP),
	DECL_API("GetVersionExW", GetVersionExW_WIN2K3),
	DECL_API("GetVersionExW", GetVersionExW_VISTA),
	DECL_API("GetVersionExW", GetVersionExW_WIN2K8),
	DECL_API("GetVolumePathNameA", GetVolumePathNameA_new),
	DECL_API("GetVolumePathNameW", GetVolumePathNameW_new),
	DECL_API("GetWindowsDirectoryW", GetWindowsDirectoryW_new),
	DECL_API("GlobalAddAtomW", GlobalAddAtomW_new),
	DECL_API("GlobalFindAtomW", GlobalFindAtomW_new),
	DECL_API("GlobalGetAtomNameW", GlobalGetAtomNameW_new),
	DECL_API("GlobalLock", GlobalLock_fix),
	DECL_API("GlobalMemoryStatusEx", GlobalMemoryStatusEx_new),
	DECL_API("GlobalUnlock", GlobalUnlock_fix),
	DECL_API("HeapLock", HeapLock_new),
	DECL_API("HeapSetInformation", HeapSetInformation_stub),
	DECL_API("HeapUnlock", HeapUnlock_new),
	DECL_API("InitializeCriticalSectionAndSpinCount", InitializeCriticalSectionAndSpinCount_new),
	DECL_API("IsProcessInJob", IsProcessInJob_new),
	DECL_API("IsProcessorFeaturePresent", IsProcessorFeaturePresent_new),
	DECL_API("IsValidLanguageGroup", IsValidLanguageGroup_stub),
	DECL_API("IsWow64Process", IsWow64Process_new),
	DECL_API("KEXVersion", KEXVersion),
	DECL_API("LCMapStringW", LCMapStringW_new),
	DECL_API("LoadLibraryExW", LoadLibraryExW_new),
	DECL_API("LoadLibraryW", LoadLibraryW_new),
	DECL_API("LockFileEx", LockFileEx_new),
	DECL_API("MapViewOfFile", MapViewOfFile_new),
	DECL_API("MapViewOfFileEx", MapViewOfFileEx_new),
	DECL_API("Module32FirstW", Module32FirstW_new),
	DECL_API("Module32NextW", Module32NextW_new),
	DECL_API("MoveFileExA", MoveFileExA_new),
	DECL_API("MoveFileExW", MoveFileExW_new),
	DECL_API("MoveFileW", MoveFileW_new),
	DECL_API("MoveFileWithProgressA", MoveFileWithProgressA_new),
	DECL_API("MoveFileWithProgressW", MoveFileWithProgressW_new),
	DECL_API("MultiByteToWideChar", MultiByteToWideChar_new),
	DECL_API("OpenJobObjectA", OpenJobObjectA_new),
	DECL_API("OpenJobObjectW", OpenJobObjectW_new),
	DECL_API("OpenThread", OpenThread_new),
	DECL_API("OutputDebugStringW", OutputDebugStringW_new),
	DECL_API("PostQueuedCompletionStatus", PostQueuedCompletionStatus_new),
	DECL_API("Process32FirstW", Process32FirstW_new),
	DECL_API("Process32NextW", Process32NextW_new),
	DECL_API("ProcessIdToSessionId", ProcessIdToSessionId_new),
	DECL_API("QueryInformationJobObject", QueryInformationJobObject_new),
	DECL_API("ReadConsoleInputW", ReadConsoleInputW_new),
	DECL_API("ReadFile", ReadFile_fix),
	DECL_API("RemoveDirectoryW", RemoveDirectoryW_new),
	DECL_API("ReplaceFileA", ReplaceFileA_stub),
	DECL_API("ReplaceFileW", ReplaceFileW_stub),
	DECL_API("RestoreLastError", SetLastError),
	DECL_API("RtlCaptureContext", RtlCaptureContext_new),
	DECL_API("RtlCaptureStackBackTrace", RtlCaptureStackBackTrace_stub),
	DECL_API("SearchPathW", SearchPathW_new),
	DECL_API("SetConsoleTitleW", SetConsoleTitleW_new),
	DECL_API("SetCurrentDirectoryW", SetCurrentDirectoryW_new),
	DECL_API("SetDllDirectoryA", SetDllDirectoryA_new),
	DECL_API("SetDllDirectoryW", SetDllDirectoryW_new),
	DECL_API("SetFileAttributesW", SetFileAttributesW_new),
	DECL_API("SetFilePointerEx", SetFilePointerEx_new),
	DECL_API("SetInformationJobObject", SetInformationJobObject_new),
	DECL_API("SetThreadUILanguage", SetThreadUILanguage_new),
	DECL_API("SystemTimeToTzSpecificLocalTime", SystemTimeToTzSpecificLocalTime_new),
	DECL_API("TerminateJobObject", TerminateJobObject_new),
	DECL_API("TryEnterCriticalSection", TryEnterCriticalSection_new),
	DECL_API("TzSpecificLocalTimeToSystemTime", TzSpecificLocalTimeToSystemTime_new),
	DECL_API("UnlockFileEx", UnlockFileEx_new),
	DECL_API("VerLanguageNameW", VerLanguageNameW_new),
	DECL_API("VerSetConditionMask", VerSetConditionMask_new),
	DECL_API("VerifyVersionInfoA", VerifyVersionInfoA_NT2K),
	DECL_API("VerifyVersionInfoA", VerifyVersionInfoA_WINXP),
	DECL_API("VerifyVersionInfoA", VerifyVersionInfoA_WIN2K3),
	DECL_API("VerifyVersionInfoA", VerifyVersionInfoA_VISTA),
	DECL_API("VerifyVersionInfoA", VerifyVersionInfoA_WIN2K8),
	DECL_API("VerifyVersionInfoW", VerifyVersionInfoW_NT2K),
	DECL_API("VerifyVersionInfoW", VerifyVersionInfoW_WINXP),
	DECL_API("VerifyVersionInfoW", VerifyVersionInfoW_WIN2K3),
	DECL_API("VerifyVersionInfoW", VerifyVersionInfoW_VISTA),
	DECL_API("VerifyVersionInfoW", VerifyVersionInfoW_WIN2K8),
	DECL_API("VirtualAllocEx", VirtualAllocEx_new),
	DECL_API("VirtualFreeEx", VirtualFreeEx_new),
	DECL_API("WTSGetActiveConsoleSessionId", WTSGetActiveConsoleSessionId_new),
	DECL_API("WideCharToMultiByte", WideCharToMultiByte_new),
	DECL_API("WriteFile", WriteFile_fix),
	DECL_API("lstrcmpW", lstrcmpW_new),
	DECL_API("lstrcmpiW", lstrcmpiW_new),
	DECL_API("lstrcpynW", lstrcpynW_new),
/*** AUTOGENERATED APILIST NAMED EXPORTS END ***/
};

#if 0
static const apilib_unnamed_api kernel32_ordinal_apis[] =
{
/*** AUTOGENERATED APILIST ORDINAL EXPORTS BEGIN ***/
/*** AUTOGENERATED APILIST ORDINAL EXPORTS END ***/
};
#endif

const apilib_api_table apitable_kernel32 = DECL_TAB("KERNEL32.DLL", kernel32_named_apis, 0 /*kernel32_ordinal_apis*/);
