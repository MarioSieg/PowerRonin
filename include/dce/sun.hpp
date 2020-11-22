// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: sun.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 20.11.2020 15:04

#pragma once

#include "mathlib.hpp"

namespace dce {
	[[nodiscard]] extern auto calculate_sun_dir(float _hour, float _latitude, const float _delta, const Vector3<>& _up, const Vector3<>& _north) noexcept -> Vector3<>;

	[[nodiscard]] extern auto calculate_sun_orbit(const float _month, const float _ecliptic_obliquity) noexcept -> float;
}
