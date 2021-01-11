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

#include "../include/power_ronin/procinfo.hpp"
#include "../include/power_ronin/env.hpp"

#if OS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <fstream>
#endif


namespace power_ronin
{
	auto executable_name() -> std::string
	{
#if OS_WINDOWS
		char buf[MAX_PATH];
		GetModuleFileNameA(nullptr, buf, MAX_PATH);
		return buf;
#else /* POSIX */
		std::string sp;
		std::ifstream("/proc/self/comm") >> sp;
		return sp;
#endif
	}

	auto process_memory_usage() -> std::size_t
	{
		return 0;
	}
}
