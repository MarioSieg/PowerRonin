#pragma once

#include <ctime>
#include <string>

namespace power_ronin
{
	/// <summary>
	/// Safe alternative for std::localtime
	/// </summary>
	/// <param name="_time"></param>
	/// <returns></returns>
	[[nodiscard]] extern auto safe_localtime(const std::time_t& _time) -> std::tm;

	/// <summary>
	/// Returns safe_localtime as timestamp string.
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] extern auto time_stamp() -> std::string;

	/// <summary>
	/// Writes safe_localtime as timestamp string into a fixed buffer.
	/// </summary>
	/// <param name="_buffer"></param>
	extern void time_stamp(char (&_buffer)[32]);
}
