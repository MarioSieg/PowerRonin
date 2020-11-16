// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: theme.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "../../include/dce/config.hpp"

namespace dce::gui {
	extern void style_dark() noexcept;
	extern void style_light() noexcept;
	extern void style_cherry() noexcept;
	extern void style_blue() noexcept;
	extern void style_green() noexcept;
	extern void style_alpha_apply(float alpha = 1.F) noexcept;
	extern void style_antialiasing_apply(bool enable_aa = true) noexcept;
	extern void style_rounding_apply(float rounding = .0F) noexcept;
	extern void style_apply(SystemStyle style) noexcept;
} // namespace dce::gui // namespace dce::gui
