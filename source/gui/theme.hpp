#pragma once

#include "../../Include/PowerRonin/Config.hpp"

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
