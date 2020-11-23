// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: misc.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 22.11.2020 18:38

#include "../../include/dce/core/misc.hpp"
#include "../../include/dce/utils.hpp"
#include "../../include/dce/env.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

#if SYS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace dce::core {

	void call_to_interrupt() {
#if COM_MSVC
		__debugbreak();
#elif CPU_ARM
		asm("bkpt 0");
#elif CPU_X86 && (COM_GCC || COM_CLANG)
		__asm__ __volatile__("int $3");
#else
		int* int3 = reinterpret_cast<int*>(3L);
		*int3 = 3;
#endif
	}

#if SYS_WINDOWS
#define CALL_FIRST 1
#define CALL_LAST 0

	auto WINAPI handler(struct _EXCEPTION_POINTERS* const _info) -> LONG {
		if (_info->ExceptionRecord->ExceptionCode != EXCEPTION_BREAKPOINT) {
			return EXCEPTION_CONTINUE_SEARCH;
		}
		PCONTEXT context = _info->ContextRecord;

		/* The int $3 instruction is one byte in size. So we need to increment the instruction pointers to continue. */
#ifdef _AMD64_
		++context->Rip;
#else
		++context->Eip;
#endif

		if (!std::filesystem::is_directory("crashes")) {
			std::filesystem::create_directory("crashes");
		}
		std::stringstream ss;
		const auto now = std::time(nullptr);
		const auto tm = safe_localtime(now);
		ss << "crashes/" << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S") << ".crash";
		std::ofstream file(ss.str());
		ss.str("");
		ss << "MSG: Fatal breakpoint at @" << std::hex << _info->ExceptionRecord->ExceptionAddress;
		[[likely]] if (file) {
			file << ss.str();
		}
		std::cerr << ss.str();

		return EXCEPTION_CONTINUE_EXECUTION;
	}

	ScopedVectoredExceptionHandler::ScopedVectoredExceptionHandler() : handler_(&handler_) {
		AddVectoredExceptionHandler(CALL_FIRST, &handler);
	}

	ScopedVectoredExceptionHandler::~ScopedVectoredExceptionHandler() {
		RemoveVectoredExceptionHandler(this->handler_);
	}

#else
	
	ScopedVectoredExceptionHandler::ScopedVectoredExceptionHandler() {

	}

	ScopedVectoredExceptionHandler::~ScopedVectoredExceptionHandler() {

	}
	
#endif

	void create_fatal_dump() {
		if (!std::filesystem::is_directory("crashes")) {
			std::filesystem::create_directory("crashes");
		}
		std::stringstream ss;
		const auto now = std::time(nullptr);
		const auto tm = safe_localtime(now);
		ss << "crashes/" << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S") << ".crash";
		std::ofstream file(ss.str());
		ss.str("");
		ss << "MSG: Fatal unknown error!";
		[[likely]] if (file) {
			file << ss.str();
		}
		std::cerr << ss.str();
	}

	void create_fatal_dump(const std::exception& _ex) {
		if (!std::filesystem::is_directory("crashes")) {
			std::filesystem::create_directory("crashes");
		}
		std::stringstream ss;
		const auto now = std::time(nullptr);
		const auto tm = safe_localtime(now);
		ss << "crashes/" << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S") << ".crash";
		std::ofstream file(ss.str());
		ss.str("");
		ss << "MSG: " << _ex.what();
		[[likely]] if (file) {
			file << ss.str();
		}
		std::cerr << ss.str();
	}

	void create_fatal_dump(const FatalEngineException& _ex) {
		if (!std::filesystem::is_directory("crashes")) {
			std::filesystem::create_directory("crashes");
		}
		std::stringstream ss;
		const auto now = std::time(nullptr);
		const auto tm = safe_localtime(now);
		ss << "crashes/" << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S") << ".crash";
		std::ofstream file(ss.str());
		ss.str("");
		ss << "MSG: " << _ex.what();
		ss << "\nFile: " << _ex.get_source_file();
		ss << "\nLine: " << _ex.get_source_line();
		[[likely]] if (file) {
			file << ss.str();
		}
		std::cerr << ss.str();
	}
}
