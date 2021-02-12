#pragma once

#include "MathLib.hpp"

namespace PowerRonin
{
	[[nodiscard]] extern auto calculate_sun_dir(const float _hour
	                                            , const float _latitude
	                                            , const float _delta
	                                            , const Vector3<>& _up
	                                            , const Vector3<>& _north) noexcept -> Vector3<>;

	[[nodiscard]] extern auto calculate_sun_orbit(float _month, float _ecliptic_obliquity) noexcept -> float;
}
