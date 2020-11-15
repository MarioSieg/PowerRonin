// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: imgui_input.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

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
