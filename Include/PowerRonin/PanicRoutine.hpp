#pragma once

#include <string_view>

namespace PowerRonin
{
	extern void GlobalPanicRoutine(const std::string_view msg, const std::size_t line = 0, const std::string_view file = "Unknown");
}
