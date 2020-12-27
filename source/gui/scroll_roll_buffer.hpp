#pragma once

#include "gui_headers.hpp"

namespace dce::gui {
	// utility structure for realtime plot
	struct ScrollingBuffer final {
		int max_size;
		int offset;
		ImVector<ImVec2> data;

		ScrollingBuffer();

		void add_point(float _x, float _y);
		void erase();
	};

	// Utility structure for realtime plot.
	struct RollingBuffer {
		float span;
		ImVector<ImVec2> data;

		RollingBuffer();

		void add_point(float _x, float _y);
	};
} // namespace dce::gui::widgets // namespace dce::gui::widgets
