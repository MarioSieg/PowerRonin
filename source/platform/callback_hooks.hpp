// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

struct GLFWwindow;

namespace dce::platform {
	/* Mouse button callback hook. */
	void mouse_button_callback([[maybe_unused]] GLFWwindow* _win
	                           , [[maybe_unused]] int _button
	                           , [[maybe_unused]] int _action
	                           , [[maybe_unused]] int _mods) noexcept;

	/* Mouse scrolling callback hook. */
	void scroll_callback([[maybe_unused]] GLFWwindow* _win, [[maybe_unused]] double _x, [[maybe_unused]] double _y) noexcept;

	/* Keyboard key press callback hook. */
	void key_callback([[maybe_unused]] GLFWwindow* _win
	                  , int _key
	                  , [[maybe_unused]] int _scancode
	                  , int _action
	                  , [[maybe_unused]] int _mods) noexcept;

	/* Character input callback hook. */
	void char_callback([[maybe_unused]] GLFWwindow* _win, unsigned _c) noexcept;

	/* Ugly and hacky way to get the mouse states into a global function. */
	extern bool (*MOUSE_STATES)[5];
} // namespace dce::platform // namespace dce::platform
