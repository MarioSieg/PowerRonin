#pragma once

#include <string>
#include <cstddef>

namespace power_ronin
{
	/// <summary>
	/// Returns the name of the executable.
	/// </summary>
	[[nodiscard]] extern auto executable_name() -> std::string;

	/// <summary>
	///
	/// </summary>
	/// <returns>The amount of RAM memory used by the process in bytes.</returns>
	[[nodiscard]] extern auto process_memory_usage() -> std::size_t;
}
