#include "../Include/PowerRonin/TimeUtils.hpp"
#include "../../Include/PowerRonin/Platform.hpp"
#include <mutex>

namespace PowerRonin
{
	auto safe_localtime(const std::time_t& _time) -> std::tm
	{
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

	auto time_stamp() -> std::string
	{
		auto bt = safe_localtime(std::time(nullptr));
		char buf[64];
		return {buf, std::strftime(buf, sizeof buf, "%F %T", &bt)};
	}

	void time_stamp(char ( &_buffer)[32])
	{
		auto bt = safe_localtime(std::time(nullptr));
		std::strftime(_buffer, sizeof _buffer, "%F %T", &bt);
	}
}
