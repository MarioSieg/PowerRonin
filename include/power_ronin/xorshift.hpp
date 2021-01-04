#pragma once

#include<cstdint>

namespace power_ronin
{
	[[nodiscard]] extern auto xorshift32() noexcept -> std::uint32_t;

	[[nodiscard]] extern auto xorshift64() noexcept -> std::uint64_t;

	[[nodiscard]] extern auto xorshift128() noexcept -> std::uint32_t;
} // namespace power_ronin
