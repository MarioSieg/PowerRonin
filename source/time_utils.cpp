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

#include "../include/power_ronin/time_utils.hpp"
#include "../../include/power_ronin/env.hpp"
#include <mutex>

namespace power_ronin
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
