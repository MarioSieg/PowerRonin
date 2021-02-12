#pragma once

namespace PowerRonin
{
	extern void ReadFence() noexcept;
	extern void WriteFence() noexcept;
	extern void ReadWriteFence() noexcept;
	extern void MemoryFence() noexcept;
}
