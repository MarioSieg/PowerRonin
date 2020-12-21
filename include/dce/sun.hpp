#pragma once

#include "mathlib.hpp"

namespace dce {
	[[nodiscard]] extern auto calculate_sun_dir(float _hour
	                                            , float _latitude
	                                            , float _delta
	                                            , const Vector3<>& _up
	                                            , const Vector3<>& _north) noexcept -> Vector3<>;

	[[nodiscard]] extern auto calculate_sun_orbit(float _month, float _ecliptic_obliquity) noexcept -> float;
}
