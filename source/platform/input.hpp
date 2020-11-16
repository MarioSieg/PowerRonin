// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: input.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

struct GLFWcursor;

namespace dce::platform {
	class GuiInput final {
	public:
		auto initialize() -> bool;
		void update();
		void shutdown();
		void update_mouse();
		void update_cursor();
		static void update_gamepads();
		void install_callback_procedures() const;

	private:
		bool mouse_buttons[5] = {};
		GLFWcursor *cursors[9] = {};
		double timer = .0;
		void *window = nullptr;
	};
} // namespace dce::platform // namespace dce::platform
