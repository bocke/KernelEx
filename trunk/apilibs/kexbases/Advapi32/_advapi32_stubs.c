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

#include "common.h"

UNIMPL_FUNC(CryptAcquireContextW, 5); //all MSLU does is to load this function from advapi32 so it loops...
UNIMPL_FUNC(CryptEnumProvidersW, 6); //so it loops...
UNIMPL_FUNC(CryptEnumProviderTypesW, 6); //so it loops...
UNIMPL_FUNC(CryptGetDefaultProviderW, 5); //so it loops...
UNIMPL_FUNC(CryptSetProviderExW, 4); //...
UNIMPL_FUNC(CryptSetProviderW, 2); //...
UNIMPL_FUNC(CryptSignHashW, 6); //...
UNIMPL_FUNC(CryptVerifySignatureW, 6); //...

UNIMPL_FUNC(ConvertSidToStringSidA, 2);
UNIMPL_FUNC(ConvertStringSidToSidA, 2);
UNIMPL_FUNC(ConvertSidToStringSidW, 2);
UNIMPL_FUNC(ConvertStringSidToSidW, 2);
UNIMPL_FUNC(RegOverridePredefKey, 2);
UNIMPL_FUNC(IsWellKnownSid, 2);

UNIMPL_FUNC(ConvertStringSecurityDescriptorToSecurityDescriptorA, 4);
UNIMPL_FUNC(ConvertStringSecurityDescriptorToSecurityDescriptorW, 4);

UNIMPL_FUNC(ConvertSecurityDescriptorToStringSecurityDescriptorA, 5);
UNIMPL_FUNC(ConvertSecurityDescriptorToStringSecurityDescriptorW, 5);
