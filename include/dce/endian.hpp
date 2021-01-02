#pragma once

#include <cstdint>

namespace dce
{
	constexpr auto endian_swap(const std::int16_t in) noexcept
	{
		return static_cast<std::int16_t>(endian_swap(static_cast<std::uint16_t>(in)));
	}

	constexpr auto endian_swap(const std::uint16_t in) noexcept
	{
		return in >> 8 | in << 8;
	}

	constexpr auto endian_swap(const std::int32_t in) noexcept
	{
		return static_cast<std::int32_t>(endian_swap(static_cast<std::uint32_t>(in)));
	}

	constexpr auto endian_swap(const std::uint32_t in) noexcept
	{
		return in >> 24 | in << 24 | (in & 0x00ff0000) >> 8 | (in & 0x0000ff00) << 8;
	}

	constexpr auto endian_swap(const std::int64_t in) noexcept
	{
		return static_cast<std::int64_t>(endian_swap(static_cast<std::uint64_t>(in)));
	}

	constexpr auto endian_swap(const std::uint64_t in) noexcept
	{
		return in >> 56 | in << 56 | (in & UINT64_C(0x00ff000000000000)) >> 40 | (in & UINT64_C(0x000000000000ff00)) <<
			40 | (in &
				UINT64_C(0x0000ff0000000000)) >> 24 | (in & UINT64_C(0x0000000000ff0000)) << 24 | (in & UINT64_C(
					0x000000ff00000000)
			) >>
			8 | (in & UINT64_C(0x00000000ff000000)) << 8;
	}
} // namespace dce // namespace dce
