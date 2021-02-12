#pragma once

#include <cstdint>

namespace PowerRonin
{
	class Chrono;

	namespace Renderer
	{
		extern auto update_clocks(Chrono& _chrono, std::uint64_t _prev) noexcept -> std::uint64_t;
	}
}
