#include "../Include/PowerRonin/InterruptHandler.hpp"
#include "../Include/PowerRonin/Platform.hpp"
#include "../Include/PowerRonin/TimeUtils.hpp"

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
