// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#pragma once

#include "mathtypes.hpp"

namespace PowerRonin::Math
{
	inline auto RgbaToRgbaNorm(const std::uint32_t _rgba) noexcept -> Color<>
	{
		return Color<>{
			(_rgba >> 24 & 0xFF) / 255.f, (_rgba >> 16 & 0xFF) / 255.f, (_rgba >> 8 & 0xFF) / 255.f,
			(_rgba & 0xFF) / 255.f
		};
	}

	template <typename T> requires requires
	{
		requires std::is_integral_v<T> || std::is_floating_point_v<T>;
	} constexpr auto MapRange(const T _x, const T _in_min, const T _in_max, const T _out_min, const T _out_max) noexcept -> T
	{
		return (_x - _in_min) * (_out_max - _out_min) / (_in_max - _in_min) + _out_min;
	}
}
