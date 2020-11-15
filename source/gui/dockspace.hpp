// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: dockspace.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#pragma once

namespace dce::gui {
	constexpr auto IS_FULLSCREEN_DOCKSPACE = true;
	constexpr auto IS_PADDING_DOCKSPACE = false;

	extern void begin_dockspace();
	extern void end_dockspace();
} // namespace dce::gui
