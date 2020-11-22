// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: sun.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 20.11.2020 15:05

#include "../../include/dce/sun.hpp"
#include <cmath>

namespace dce {
	auto calculate_sun_dir(float _hour, float _latitude, const float _delta, const Vector3<>& _up, const Vector3<>& _north) noexcept -> Vector3<> {
		_latitude = math::radians(_latitude);
		_hour *= math::pi<float>() / 12.f;
		const auto azimuth = std::atan2(std::sin(_hour), std::cos(_hour) * std::sin(_latitude) - std::tan(_delta) * std::cos(_latitude));
		const auto altitude = std::asin(std::sin(_latitude) * std::sin(_delta) + std::cos(_latitude) * std::cos(_delta) * std::cos(_hour));
		auto rotation = math::identity<Quaternion<>>();
		rotation = rotate(rotation, -azimuth, _up);
		const Vector3<> dir = _north * rotation;
		const Vector3<> udx = cross(_up, dir);
		rotation = math::identity<Quaternion<>>();
		rotate(rotation, altitude, udx);
		return dir * rotation;
	}

	auto calculate_sun_orbit(const float _month, const float _ecliptic_obliquity) noexcept -> float {
		const auto day = 30.f * _month + 15.f;
		const auto lambda = math::radians(280.46f + 0.9856474f * day);
		return std::asin(std::sin(_ecliptic_obliquity) * std::sin(lambda));
	}
}
