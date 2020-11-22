// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: callback_hooks.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

struct GLFWwindow;

namespace dce::platform {
	/* Mouse button callback hook. */
	void mouse_button_callback([[maybe_unused]] GLFWwindow* _win, [[maybe_unused]] int _button, [[maybe_unused]] int _action, [[maybe_unused]] int _mods) noexcept;

	/* Mouse scrolling callback hook. */
	void scroll_callback([[maybe_unused]] GLFWwindow* _win, [[maybe_unused]] double _x, [[maybe_unused]] double _y) noexcept;

	/* Keyboard key press callback hook. */
	void key_callback([[maybe_unused]] GLFWwindow* _win, int _key, [[maybe_unused]] int _scancode, int _action, [[maybe_unused]] int _mods) noexcept;

	/* Character input callback hook. */
	void char_callback([[maybe_unused]] GLFWwindow* _win, unsigned _c) noexcept;

	/* Ugly and hacky way to get the mouse states into a global function. */
	extern bool (*MOUSE_STATES)[5];
} // namespace dce::platform // namespace dce::platform
