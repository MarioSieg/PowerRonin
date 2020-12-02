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

#include "../include/dce/utils.hpp"
#include "../../include/dce/env.hpp"
#include <mutex>

#if SYS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <fstream>
#endif

namespace dce {
	FatalEngineException::FatalEngineException() : std::runtime_error("Fatal engine system error!") { }

	FatalEngineException::FatalEngineException(const std::string& _msg) : std::runtime_error(_msg) { }

	FatalEngineException::FatalEngineException(const char* const _msg) : std::runtime_error(_msg) { }

	FatalEngineException::FatalEngineException(const char* const _msg, const int _line, const char* const _file) : std::runtime_error(_msg), line_(_line), file_(_file) { }

	auto FatalEngineException::what() const noexcept -> const char* {
		return std::runtime_error::what();
	}

	auto FatalEngineException::get_source_file() const noexcept -> const char* {
		return this->file_;
	}

	auto FatalEngineException::get_source_line() const noexcept -> int {
		return this->line_;
	}

	auto safe_localtime(const std::time_t& _time) -> std::tm {
		std::tm buffer = {};
#if COM_GCC
		localtime_r(&_time, &buffer);
#elif COM_MSVC
		localtime_s(&buffer, &_time);
#else
		static std::mutex mtx;
		std::lock_guard<std::mutex> lock(mtx);
		buffer = *std::localtime(&_time);
#endif
		return buffer;
	}

	auto time_stamp() -> std::string {
		auto bt = safe_localtime(std::time(nullptr));
		char buf[64];
		return {buf, std::strftime(buf, sizeof buf, "%F %T", &bt)};
	}

	void time_stamp(char ( &_buffer)[32]) {
		auto bt = safe_localtime(std::time(nullptr));
		std::strftime(_buffer, sizeof _buffer, "%F %T", &bt);
	}

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
}
