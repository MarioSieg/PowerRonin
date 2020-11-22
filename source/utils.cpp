// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: utils.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 22.11.2020 19:08

#include "../include/dce/utils.hpp"
#include "../../include/dce/utils.hpp"
#include "../../include/dce/env.hpp"
#include <mutex>

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
}
