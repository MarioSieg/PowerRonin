#pragma once

namespace power_ronin
{
	extern void read_fence() noexcept;
	extern void write_fence() noexcept;
	extern void read_write_fence() noexcept;
	extern void memory_fence() noexcept;
}
