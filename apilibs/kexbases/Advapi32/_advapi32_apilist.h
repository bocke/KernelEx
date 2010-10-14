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

#ifndef _ADVAPI32_APILIST_H
#define _ADVAPI32_APILIST_H

#include "kexcoresdk.h"

BOOL init_advapi32();
extern const apilib_api_table apitable_advapi32;

/*** AUTOGENERATED APILIST DECLARATIONS BEGIN ***/
SC_HANDLE WINAPI OpenSCManagerA_stub(LPCSTR lpMachineName, LPCSTR lpDatabaseName, DWORD dwDesiredAccess);
SC_HANDLE WINAPI OpenSCManagerW_stub(LPCWSTR lpMachineName, LPCWSTR lpDatabaseName, DWORD dwDesiredAccess);
BOOL WINAPI RegDisablePredefinedCache_new();
LONG WINAPI RegOpenCurrentUser_new(REGSAM access, PHKEY retkey);
BOOL WINAPI SystemFunction036_new(PVOID pbBuffer, ULONG dwLen);
ULONG CDECL TraceMessage_new(ULONG64 LoggerHandle, ULONG MessageFlags, LPGUID MessageGuid, USHORT MessageNumber, ...);
STUB CryptAcquireContextW_stub;
STUB CryptEnumProvidersW_stub;
STUB CryptEnumProviderTypesW_stub;
STUB CryptGetDefaultProviderW_stub;
STUB CryptSetProviderExW_stub;
STUB CryptSetProviderW_stub;
STUB CryptSignHashW_stub;
STUB CryptVerifySignatureW_stub;
STUB ConvertSidToStringSidA_stub;
STUB ConvertStringSidToSidA_stub;
STUB ConvertSidToStringSidW_stub;
STUB ConvertStringSidToSidW_stub;
STUB RegOverridePredefKey_stub;
STUB IsWellKnownSid_stub;
STUB ConvertStringSecurityDescriptorToSecurityDescriptorA_stub;
STUB ConvertStringSecurityDescriptorToSecurityDescriptorW_stub;
STUB ConvertSecurityDescriptorToStringSecurityDescriptorA_stub;
STUB ConvertSecurityDescriptorToStringSecurityDescriptorW_stub;
STUB QueryServiceStatusEx_stub;
STUB NotifyBootConfigStatus_stub;
STUB QueryWindows31FilesMigration_stub;
STUB SynchronizeWindows31FilesAndWindowsNTRegistry_stub;
STUB EnumServicesStatusExA_stub;
STUB EnumServicesStatusExW_stub;
STUB CreateProcessWithLogonW_stub;
STUB InitiateSystemShutdownExA_stub;
STUB InitiateSystemShutdownExW_stub;
STUB FileEncryptionStatusA_stub;
STUB FileEncryptionStatusW_stub;
STUB EncryptFileA_stub;
STUB EncryptFileW_stub;
STUB DecryptFileA_stub;
STUB DecryptFileW_stub;
DWORD WINAPI LsaClose_new(IN HANDLE ObjectHandle);
ULONG WINAPI LsaNtStatusToWinError_new(DWORD Status);
DWORD WINAPI LsaOpenPolicy_new(IN PVOID SystemName, IN PVOID ObjectAttributes, IN DWORD DesiredAccess, IN OUT PHANDLE PolicyHandle);
DWORD WINAPI LsaRetrievePrivateData_new(IN HANDLE PolicyHandle, IN PVOID KeyName, OUT HANDLE* PrivateData);
DWORD WINAPI LsaStorePrivateData_new(IN HANDLE PolicyHandle, IN PVOID KeyName, IN PVOID PrivateData);
BOOL WINAPI OpenProcessToken_new(HANDLE ProcessHandle, DWORD DesiredAccess, HANDLE *TokenHandle);
BOOL WINAPI OpenThreadToken_new(HANDLE ThreadHandle, DWORD DesiredAccess, BOOL OpenAsSelf, HANDLE *TokenHandle);
BOOL WINAPI DuplicateTokenEx_new(HANDLE ExistingTokenHandle, DWORD dwDesiredAccess, LPSECURITY_ATTRIBUTES lpTokenAttributes, SECURITY_IMPERSONATION_LEVEL ImpersonationLevel, TOKEN_TYPE TokenType, PHANDLE DuplicateTokenHandle);
BOOL WINAPI DuplicateToken_new(HANDLE ExistingTokenHandle, SECURITY_IMPERSONATION_LEVEL ImpersonationLevel, PHANDLE DuplicateTokenHandle);
BOOL WINAPI AdjustTokenPrivileges_new(HANDLE TokenHandle, BOOL DisableAllPrivileges, PTOKEN_PRIVILEGES NewState, DWORD BufferLength, PTOKEN_PRIVILEGES PreviousState, LPDWORD ReturnLength);
BOOL WINAPI CheckTokenMembership_new(HANDLE TokenHandle, PSID SidToCheck, PBOOL IsMember);
BOOL WINAPI GetTokenInformation_new(HANDLE token, TOKEN_INFORMATION_CLASS tokeninfoclass, LPVOID tokeninfo, DWORD tokeninfolength, LPDWORD retlen);
BOOL WINAPI SetThreadToken_new(PHANDLE thread, HANDLE token);
BOOL WINAPI AllocateAndInitializeSid_new(PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority, BYTE nSubAuthorityCount, DWORD nSubAuthority0, DWORD nSubAuthority1, DWORD nSubAuthority2, DWORD nSubAuthority3, DWORD nSubAuthority4, DWORD nSubAuthority5, DWORD nSubAuthority6, DWORD nSubAuthority7, PSID *pSid);
PVOID WINAPI FreeSid_new(PSID pSid);
BOOL WINAPI CopySid_new(DWORD nDestinationSidLength, PSID pDestinationSid, PSID pSourceSid);
BOOL WINAPI IsValidSid_new(PSID pSid);
BOOL WINAPI EqualSid_new(PSID pSid1, PSID pSid2);
BOOL WINAPI EqualPrefixSid_new (PSID pSid1, PSID pSid2);
DWORD WINAPI GetSidLengthRequired_new(BYTE nSubAuthorityCount);
BOOL WINAPI InitializeSid_new (PSID pSid, PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority, BYTE nSubAuthorityCount);
PSID_IDENTIFIER_AUTHORITY WINAPI GetSidIdentifierAuthority_new(PSID pSid);
PDWORD WINAPI GetSidSubAuthority_new(PSID pSid, DWORD nSubAuthority);
PUCHAR WINAPI GetSidSubAuthorityCount_new (PSID pSid);
DWORD WINAPI GetLengthSid_new (PSID pSid);
BOOL WINAPI InitializeSecurityDescriptor_new(SECURITY_DESCRIPTOR *pDescr, DWORD revision);
DWORD WINAPI GetSecurityDescriptorLength_new(SECURITY_DESCRIPTOR *pDescr);
BOOL WINAPI GetSecurityDescriptorOwner_new(SECURITY_DESCRIPTOR *pDescr, PSID *Owner, LPBOOL OwnerDefaulted);
BOOL WINAPI SetSecurityDescriptorOwner_new(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID owner, BOOL ownerdefaulted);
BOOL WINAPI GetSecurityDescriptorGroup_new(PSECURITY_DESCRIPTOR SecurityDescriptor, PSID *Group, LPBOOL GroupDefaulted);
BOOL WINAPI SetSecurityDescriptorGroup_new (PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID group, BOOL groupdefaulted);
BOOL WINAPI IsValidSecurityDescriptor_new(PSECURITY_DESCRIPTOR pSecurityDescriptor);
BOOL WINAPI GetSecurityDescriptorDacl_new(IN PSECURITY_DESCRIPTOR pSecurityDescriptor, OUT LPBOOL lpbDaclPresent, OUT PACL *pDacl, OUT LPBOOL lpbDaclDefaulted);
BOOL WINAPI SetSecurityDescriptorDacl_new (PSECURITY_DESCRIPTOR pSecurityDescriptor, BOOL daclpresent, PACL dacl, BOOL dacldefaulted);
BOOL WINAPI GetSecurityDescriptorSacl_new(IN PSECURITY_DESCRIPTOR pSecurityDescriptor, OUT LPBOOL lpbSaclPresent, OUT PACL *pSacl, OUT LPBOOL lpbSaclDefaulted);
BOOL WINAPI SetSecurityDescriptorSacl_new (PSECURITY_DESCRIPTOR pSecurityDescriptor, BOOL saclpresent, PACL sacl, BOOL sacldefaulted);
BOOL WINAPI MakeSelfRelativeSD_new(IN PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor, IN PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor, IN OUT LPDWORD lpdwBufferLength);
BOOL WINAPI GetSecurityDescriptorControl_new (PSECURITY_DESCRIPTOR pSecurityDescriptor, PSECURITY_DESCRIPTOR_CONTROL pControl, LPDWORD lpdwRevision);
BOOL WINAPI InitializeAcl_new(PACL acl, DWORD size, DWORD rev);
BOOL WINAPI LookupPrivilegeValueW_new(LPCWSTR lpSystemName, LPCWSTR lpName, PLUID lpLuid);
BOOL WINAPI LookupPrivilegeValueA_new(LPCSTR lpSystemName, LPCSTR lpName, PLUID lpLuid);
BOOL WINAPI GetFileSecurityW_new(LPCWSTR lpFileName, SECURITY_INFORMATION RequestedInformation, SECURITY_DESCRIPTOR* pSecurityDescriptor, DWORD nLength, LPDWORD lpnLengthNeeded);
BOOL WINAPI GetFileSecurityA_new(LPCSTR lpFileName, SECURITY_INFORMATION RequestedInformation, SECURITY_DESCRIPTOR* pSecurityDescriptor, DWORD nLength, LPDWORD lpnLengthNeeded);
BOOL WINAPI LookupAccountSidA_new(IN LPCSTR system, IN PSID sid, OUT LPSTR account, IN OUT LPDWORD accountSize, OUT LPSTR domain, IN OUT LPDWORD domainSize, OUT PSID_NAME_USE name_use);
BOOL WINAPI LookupAccountSidW_new(IN LPCWSTR system, IN PSID sid, OUT LPWSTR account, IN OUT LPDWORD accountSize, OUT LPWSTR domain, IN OUT LPDWORD domainSize, OUT PSID_NAME_USE name_use);
BOOL WINAPI SetFileSecurityA_new(LPCSTR lpFileName, SECURITY_INFORMATION RequestedInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor);
BOOL WINAPI SetFileSecurityW_new(LPCWSTR lpFileName, SECURITY_INFORMATION RequestedInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor);
BOOL WINAPI RevertToSelf_new(void);
BOOL WINAPI ImpersonateSelf_new(SECURITY_IMPERSONATION_LEVEL ImpersonationLevel);
BOOL WINAPI AccessCheck_new(PSECURITY_DESCRIPTOR SecurityDescriptor, HANDLE ClientToken, DWORD DesiredAccess, PGENERIC_MAPPING GenericMapping, PPRIVILEGE_SET PrivilegeSet, LPDWORD PrivilegeSetLength, LPDWORD GrantedAccess, LPBOOL AccessStatus);
BOOL WINAPI SetKernelObjectSecurity_new (IN HANDLE Handle, IN SECURITY_INFORMATION SecurityInformation, IN PSECURITY_DESCRIPTOR SecurityDescriptor);
BOOL WINAPI PrivilegeCheck_new(HANDLE ClientToken, PPRIVILEGE_SET RequiredPrivileges, LPBOOL pfResult);
BOOL WINAPI AddAccessAllowedAce_new(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD AccessMask, IN PSID pSid);
BOOL WINAPI GetAce_new(PACL pAcl,DWORD dwAceIndex,LPVOID *pAce);
BOOL WINAPI DeleteAce_new(PACL pAcl, DWORD dwAceIndex);
BOOL WINAPI CreateRestrictedToken_new(HANDLE baseToken, DWORD flags, DWORD nDisableSids, PSID_AND_ATTRIBUTES disableSids, DWORD nDeletePrivs, PLUID_AND_ATTRIBUTES deletePrivs, DWORD nRestrictSids, PSID_AND_ATTRIBUTES restrictSids, PHANDLE newToken);
BOOL WINAPI CreateWellKnownSid_new(DWORD WellKnownSidType, PSID DomainSid, PSID pSid, DWORD* cbSid);
LONG WINAPI RegQueryValueExW_new(HKEY hKey, LPCWSTR lpValueNameW, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
LONG WINAPI RegEnumValueW_new(HKEY hKey, DWORD dwIndex, LPWSTR lpValueName, LPDWORD lpcValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
/*** AUTOGENERATED APILIST DECLARATIONS END ***/

#endif
