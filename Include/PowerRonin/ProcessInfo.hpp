#pragma once

#include <string>
#include <cstddef>

namespace PowerRonin
{
	/// <summary>
	/// Returns the name of the executable.
	/// </summary>
	[[nodiscard]] extern auto ExecutableName() -> std::string;

	/// <summary>
	///
	/// </summary>
	/// <returns>The amount of RAM memory used by the process in bytes.</returns>
	[[nodiscard]] extern auto ProcessMemoryUsage() -> std::size_t;
}
