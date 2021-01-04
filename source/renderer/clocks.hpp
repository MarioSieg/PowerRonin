#pragma once

#include <cstdint>

namespace power_ronin
{
	class Chrono;

	namespace renderer
	{
		extern auto update_clocks(Chrono& _chrono, std::uint64_t _prev) noexcept -> std::uint64_t;
	}
}
