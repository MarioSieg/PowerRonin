#pragma once

#include "../../include/power_ronin/config.hpp"

namespace power_ronin::gui
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
} // namespace power_ronin::gui // namespace power_ronin::gui
