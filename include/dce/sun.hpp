// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

#include "mathlib.hpp"

namespace dce {
	[[nodiscard]] extern auto calculate_sun_dir(float _hour, float _latitude, float _delta, const Vector3<>& _up, const Vector3<>& _north) noexcept -> Vector3<>;

	[[nodiscard]] extern auto calculate_sun_orbit(float _month, float _ecliptic_obliquity) noexcept -> float;
}
