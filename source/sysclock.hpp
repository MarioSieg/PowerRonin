// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: sysclock.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include <cstdint>

namespace dce {
	[[nodiscard]] auto get_high_precision_counter() noexcept -> std::uint64_t;

	[[nodiscard]] auto get_high_precision_frequency() noexcept -> std::uint64_t;
}
