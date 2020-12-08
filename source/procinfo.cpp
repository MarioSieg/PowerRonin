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

#include "../include/dce/procinfo.hpp"
#include "../include/dce/env.hpp"

#if SYS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <fstream>
#endif


namespace dce {
	auto get_executable_name() -> std::string {
#if SYS_WINDOWS
		char buf[MAX_PATH];
		GetModuleFileNameA(nullptr, buf, MAX_PATH);
		return buf;
#else /* POSIX */
		std::string sp;
		std::ifstream("/proc/self/comm") >> sp;
		return sp;
#endif
	}

	auto get_process_memory_usage() -> std::size_t {
		return 0;
	}
}
