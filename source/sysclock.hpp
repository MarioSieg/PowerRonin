#pragma once

#include <cstdint>

namespace PowerRonin
{
	[[nodiscard]] auto get_high_precision_counter() noexcept -> std::uint64_t;

	[[nodiscard]] auto get_high_precision_frequency() noexcept -> std::uint64_t;
}
