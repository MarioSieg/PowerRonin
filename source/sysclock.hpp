#pragma once

#include <cstdint>

namespace power_ronin
{
	[[nodiscard]] auto get_high_precision_counter() noexcept -> std::uint64_t;

	[[nodiscard]] auto get_high_precision_frequency() noexcept -> std::uint64_t;
}
