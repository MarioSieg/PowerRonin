// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: callback_hooks.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#include "callback_hooks.hpp"
#include "glfw_headers.hpp"
#include "../../include/dce/env.hpp"
#include "../gui/imgui_headers.hpp"

namespace dce::platform {
	bool (*MOUSE_STATES)[5] = nullptr;

	void mouse_button_callback([[maybe_unused]] GLFWwindow *const /*win*/
	                           , [[maybe_unused]] const int _button, [[maybe_unused]] const int _action
	                           , [[maybe_unused]] const int /*mods*/) noexcept {
		assert(MOUSE_STATES);
		if (_action == GLFW_PRESS && _button >= 0 && _button < static_cast<int>(sizeof *MOUSE_STATES / sizeof **MOUSE_STATES)) {
			*MOUSE_STATES[_button] = true;
		}
	}

	void scroll_callback([[maybe_unused]] GLFWwindow *const /*win*/
	                     , [[maybe_unused]] const double _x, [[maybe_unused]] const double _y) noexcept {
		auto &io = ImGui::GetIO();
		io.MouseWheelH += static_cast<float>(_x);
		io.MouseWheel += static_cast<float>(_y);
	}

	void key_callback([[maybe_unused]] GLFWwindow *const /*win*/, const int _key, [[maybe_unused]] const int /*scancode*/
	                  , const int _action, [[maybe_unused]] const int /*mods*/) noexcept {
		auto &io = ImGui::GetIO();
		io.KeysDown[_key] = _action == GLFW_PRESS;
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
#if SYS_WINDOWS
		io.KeySuper = false;
#else
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
#endif
	}

	void char_callback([[maybe_unused]] GLFWwindow *const /*win*/
	                   , const unsigned _c) noexcept {
		ImGui::GetIO().AddInputCharacter(_c);
	}
} // namespace dce::platform // namespace dce::platform
