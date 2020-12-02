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

#pragma once

#include "../env.hpp"
#include "../utils.hpp"

#if SYS_WINDOWS
#define DREAM_ENTRY WinMain /* On Windows we need WinMain */
#else
#define DREAM_ENTRY main
#endif

namespace dce::core {
	/// <summary>
	/// (ERROR ROUTINE) Creates error dump to std::cerr and a file.
	/// </summary>
	extern void create_fatal_dump();

	/// <summary>
	/// (ERROR ROUTINE) Creates error dump to std::cerr and a file.
	/// </summary>
	extern void create_fatal_dump(const std::exception& _ex);

	/// <summary>
	/// (ERROR ROUTINE) Creates error dump to std::cerr and a file.
	/// </summary>
	extern void create_fatal_dump(const FatalEngineException& _ex);


	/// <summary>
	/// Cross platform debug break (int $3)
	/// </summary>
	extern void call_to_interrupt();

	struct ScopedVectoredExceptionHandler final {
		ScopedVectoredExceptionHandler();
		ScopedVectoredExceptionHandler(const ScopedVectoredExceptionHandler&) = delete;
		ScopedVectoredExceptionHandler(ScopedVectoredExceptionHandler&&) = delete;
		auto operator=(const ScopedVectoredExceptionHandler&) = delete;
		auto operator=(ScopedVectoredExceptionHandler&&) = delete;
		~ScopedVectoredExceptionHandler();

	private:
		void* handler_ = nullptr;
	};
}
