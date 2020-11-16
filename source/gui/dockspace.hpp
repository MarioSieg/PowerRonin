// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: dockspace.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

namespace dce::gui {
	constexpr auto IS_FULLSCREEN_DOCKSPACE = true;
	constexpr auto IS_PADDING_DOCKSPACE = false;

	extern void begin_dockspace();
	extern void end_dockspace();
} // namespace dce::gui
