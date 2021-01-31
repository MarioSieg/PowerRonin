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

#include "../include/power_ronin/break_interrupt_handler.hpp"
#include "../include/power_ronin/env.hpp"
#include "../include/power_ronin/time_utils.hpp"

#include <filesystem>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

#if OS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace PowerRonin
{
#if OS_WINDOWS
#define CALL_FIRST 1
#define CALL_LAST 0

	auto WINAPI handler(struct _EXCEPTION_POINTERS* const _info) -> LONG
	{
		if (_info->ExceptionRecord->ExceptionCode != EXCEPTION_BREAKPOINT)
		{
			return EXCEPTION_CONTINUE_SEARCH;
		}
		PCONTEXT context = _info->ContextRecord;

		/* The int $3 instruction is one byte in size. So we need to increment the instruction pointers to continue. */
#ifdef _AMD64_
		++context->Rip;
#else
		++context->Eip;
#endif

		if (!std::filesystem::is_directory("crashes"))
		{
			std::filesystem::create_directory("crashes");
		}
		std::stringstream ss;
		const auto now = std::time(nullptr);
		const auto tm = safe_localtime(now);
		ss << "crashes/" << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S") << ".crash";
		std::ofstream file(ss.str());
		ss.str("");
		ss << "MSG: Fatal breakpoint at @" << std::hex << _info->ExceptionRecord->ExceptionAddress;
		if (file) [[likely]]
		{
			file << ss.str();
		}
		std::cerr << ss.str();

		return EXCEPTION_CONTINUE_EXECUTION;
	}

	ScopedVectoredExceptionHandler::ScopedVectoredExceptionHandler() : handle(&handle)
	{
		AddVectoredExceptionHandler(CALL_FIRST, &handler);
	}

	ScopedVectoredExceptionHandler::~ScopedVectoredExceptionHandler()
	{
		RemoveVectoredExceptionHandler(this->handle);
	}

#else

	ScopedVectoredExceptionHandler::ScopedVectoredExceptionHandler() {

	}

	ScopedVectoredExceptionHandler::~ScopedVectoredExceptionHandler() {

	}

#endif
}
