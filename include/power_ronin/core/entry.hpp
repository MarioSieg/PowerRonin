// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#pragma once

#include "../env.hpp"

#if SYS_WINDOWS
#define DREAM_ENTRY WinMain /* On Windows we need WinMain */
#else
#define DREAM_ENTRY main
#endif

extern auto default_power_ronin_entry(int _argc, const char** _argv, const char** _envp = nullptr) -> int;
