// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: mathlib.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "mathtypes.hpp"

namespace dce::math {

	inline const Vector3<> BACK = {0, 0, -1};
	inline const Vector3<> DOWN = {0, -1, 0};
	inline const Vector3<> FORWARD = {0, 0, 1};
	inline const Vector3<> LEFT = {-1, 0, 0};
	inline const Vector3<> RIGHT = {1, 0, 0};
	inline const Vector3<> UP = {0, 1, 0};
	inline const Vector3<> ZERO = {0, 0, 0};
	inline const Vector3<> ONE = {1, 1, 1};
	inline const Vector3<> NORTH = {0, 0, 1};
	inline const Vector3<> SOUTH = {0, 0, -1};
	inline const Vector3<> EAST = {1, 0, 0};
	inline const Vector3<> WEST = {-1, 0, 0};

	inline auto rgba_to_rgba_norm(const std::uint32_t _rgba) noexcept -> Color<> {
		return Color<>{(_rgba >> 24 & 0xFF) / 255.f, (_rgba >> 16 & 0xFF) / 255.f, (_rgba >> 8 & 0xFF) / 255.f, (_rgba & 0xFF) / 255.f};
	}
}
