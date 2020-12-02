// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "wincom.hpp"

// We cannot use #if SYS_WINDOWS
// because one of the fucking headers defines some enumerators with that name.
#if _WIN64
#include <combaseapi.h>
#endif

namespace dce {

	void co_initialize() {
#if  _WIN64
		CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
#endif
	}

	void co_uninitialize() {
#if  _WIN64
		CoUninitialize();
#endif
	}
}
