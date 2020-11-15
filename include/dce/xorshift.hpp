// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: xorshift.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#pragma once

#include<cstdint>

namespace dce {
	[[nodiscard]] extern auto xorshift32() noexcept -> std::uint32_t;

	[[nodiscard]] extern auto xorshift64() noexcept -> std::uint64_t;

	[[nodiscard]] extern auto xorshift128() noexcept -> std::uint32_t;
} // namespace dce
