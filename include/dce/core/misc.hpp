// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: misc.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

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
