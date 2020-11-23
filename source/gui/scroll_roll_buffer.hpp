// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: scroll_roll_buffer.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "gui_headers.hpp"

namespace dce::gui {
	// utility structure for realtime plot
	struct ScrollingBuffer final {
		int max_size;
		int offset;
		ImVector<ImVec2> data;

		ScrollingBuffer();

		void add_point(const float _x, const float _y);
		void erase();
	};

	// Utility structure for realtime plot.
	struct RollingBuffer {
		float span;
		ImVector<ImVec2> data;

		RollingBuffer();

		void add_point(const float _x, const float _y);
	};
} // namespace dce::gui::widgets // namespace dce::gui::widgets
