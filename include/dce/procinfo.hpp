#pragma once

#include <string>
#include <cstddef>

namespace dce {
	/// <summary>
	/// Returns the name of the executable.
	/// </summary>
	[[nodiscard]] extern auto get_executable_name() -> std::string;

	/// <summary>
	///
	/// </summary>
	/// <returns>The amount of RAM memory used by the process in bytes.</returns>
	[[nodiscard]] extern auto get_process_memory_usage() -> std::size_t;
}
