#include "../../include/power_ronin/sun.hpp"
#include <cmath>

#include "bx/math.h"

namespace power_ronin
{
	auto calculate_sun_dir(float _hour
	                       , float _latitude
	                       , const float _delta
	                       , const SimdVector3<>& _up
	                       , const SimdVector3<>& _north) noexcept -> SimdVector3<>
	{
		/*
		_latitude = math::radians(_latitude);
		_hour *= math::pi<float>() / 12.f;
		const auto azimuth = std::atan2(std::sin(_hour)
		                                , std::cos(_hour) * std::sin(_latitude) - std::tan(_delta) *
		                                std::cos(_latitude));
		const auto altitude = std::asin(
			std::sin(_latitude) * std::sin(_delta) + std::cos(_latitude) * std::cos(_delta) * std::cos(_hour));
		auto rotation = math::identity<SimdQuaternion<>>();
		rotation = rotate(rotation, -azimuth, _up);
		const SimdVector3<> dir = _north * rotation;
		const SimdVector3<> udx = cross(_up, dir);
		rotation = math::identity<SimdQuaternion<>>();
		rotate(rotation, altitude, udx);
		return dir * rotation;
		*/

		const float latitude = bx::toRad(_latitude);
		const float hh = _hour * bx::kPi / 12.0f;
		const float azimuth = bx::atan2(
			bx::sin(hh)
			, bx::cos(hh) * bx::sin(latitude) - bx::tan(_delta) * bx::cos(latitude)
		);

		const float altitude = bx::asin(
			bx::sin(latitude) * bx::sin(_delta) + bx::cos(latitude) * bx::cos(_delta) * bx::cos(hh)
		);

		const bx::Quaternion rot0 = bx::rotateAxis({.0f, 1.f, .0f}, -azimuth);
		const bx::Vec3 dir = bx::mul(bx::Vec3{1.f, .0f, .0f}, rot0);
		const bx::Vec3 uxd = bx::cross(bx::Vec3{.0f, 1.f, .0f}, dir);

		const bx::Quaternion rot1 = bx::rotateAxis(uxd, altitude);
		const auto dir2 = bx::mul(dir, rot1);
		return {dir2.x, dir2.y, dir2.z};
	}

	auto calculate_sun_orbit(const float _month, const float _ecliptic_obliquity) noexcept -> float
	{
		const auto day = 30.f * _month + 15.f;
		const auto lambda = math::radians(280.46f + 0.9856474f * day);
		return std::asin(std::sin(_ecliptic_obliquity) * std::sin(lambda));
	}
}
