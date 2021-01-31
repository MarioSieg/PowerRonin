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

#include "../../include/power_ronin/config.hpp"

namespace PowerRonin::Interface
{
	enum class SystemTheme
	{
		DARK,
		LIGHT,
		BLUE,
		GREEN,
		CHERRY,
	};

	extern void style_dark() noexcept;
	extern void style_light() noexcept;
	extern void style_cherry() noexcept;
	extern void style_blue() noexcept;
	extern void style_green() noexcept;
	extern void style_alpha_apply(float _alpha = 1.F) noexcept;
	extern void style_antialiasing_apply(bool _enable_aa = true) noexcept;
	extern void style_rounding_apply(float _rounding = .0F) noexcept;
	extern void style_apply(SystemTheme _style) noexcept;
} // namespace PowerRonin::gui // namespace PowerRonin::gui
