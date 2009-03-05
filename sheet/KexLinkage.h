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

#ifndef __KEXLINKAGE_H
#define __KEXLINKAGE_H

#pragma warning(disable:4530) //exceptions within strings class which we don't use
#include <vector>
#pragma warning(default:4530)
#include "sstring.hpp"
#include "kexcoresdk.h"

using namespace std;

class KexLinkage  
{
	struct conf
	{
		conf(const char* n, const char* d) : name(n), desc(d) {}
		sstring name;
		sstring desc;
	};

public:
	~KexLinkage();
	bool IsReady();
	
	static KexLinkage instance;
	vector<conf> confs;
	int default_index;
	kexGetModuleSettings_t m_kexGetModuleSettings;
	kexSetModuleSettings_t m_kexSetModuleSettings;

protected:
	KexLinkage();
	bool Prepare();
	
	bool m_ready;
	HMODULE hKernelEx;
};

#endif
