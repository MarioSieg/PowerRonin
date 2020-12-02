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

#include "sysclock.hpp"
#include "../include/dce/env.hpp"

#if SYS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <sys/time.h>
#endif

namespace dce {
	auto get_high_precision_counter() noexcept -> std::uint64_t {
#if SYS_WINDOWS
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return static_cast<std::uint64_t>(li.QuadPart);
#else
	  struct timeval now;
	  gettimeofday(&now, 0);
	  return now.tv_sec * UINT64_C(1000000) + now.tv_usec;
#endif
	}

	auto get_high_precision_frequency() noexcept -> std::uint64_t {
#if SYS_WINDOWS
		LARGE_INTEGER li;
		QueryPerformanceFrequency(&li);
		return li.QuadPart;
#else
	  return UINT64_C(1000000);
#endif
	}
}
