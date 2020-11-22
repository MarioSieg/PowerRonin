// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: clocks.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include <cstdint>

namespace dce {
	class Chrono;

	namespace renderer {
		extern auto update_clocks(Chrono& _chrono, const std::uint64_t _prev) noexcept -> std::uint64_t;
	}
}
