#pragma once

#include "mathlib.hpp"

namespace dce
{
	[[nodiscard]] extern auto calculate_sun_dir(const float _hour
	                                            , const float _latitude
	                                            , const float _delta
	                                            , const SimdVector3<>& _up
	                                            , const SimdVector3<>& _north) noexcept -> SimdVector3<>;

	[[nodiscard]] extern auto calculate_sun_orbit(float _month, float _ecliptic_obliquity) noexcept -> float;
}
