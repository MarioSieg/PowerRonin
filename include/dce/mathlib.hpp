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

#include "mathtypes.hpp"

/* Sadly we cannot use constexpr here because glm is C++ 11. */

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
		return Color < >
		{
			(_rgba >> 24 & 0xFF) / 255.f, (_rgba >> 16 & 0xFF) / 255.f, (_rgba >> 8 & 0xFF) / 255.f, (_rgba & 0xFF) / 255.f
		};
	}
}
