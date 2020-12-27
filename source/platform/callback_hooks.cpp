#include "callback_hooks.hpp"
#include "platform_headers.hpp"
#include "../../include/dce/env.hpp"
#include "../gui/gui_headers.hpp"

namespace dce::platform {
	bool (*MOUSE_STATES)[5] = nullptr;

	void mouse_button_callback([[maybe_unused]] GLFWwindow* const
	                           , [[maybe_unused]] const int _button
	                           , [[maybe_unused]] const int _action
	                           , [[maybe_unused]] const int _mods) noexcept {
		assert(MOUSE_STATES);
		[[likely]] if (_action == GLFW_PRESS && _button >= 0 && _button < static_cast<int>(sizeof *MOUSE_STATES / sizeof
			**
			MOUSE_STATES)) {
			*MOUSE_STATES[_button] = true;
		}
	}

	void scroll_callback([[maybe_unused]] GLFWwindow* const
	                     , [[maybe_unused]] const double _x
	                     , [[maybe_unused]] const double _y) noexcept {
		auto& io = ImGui::GetIO();
		io.MouseWheelH += static_cast<float>(_x);
		io.MouseWheel += static_cast<float>(_y);
	}

	void key_callback([[maybe_unused]] GLFWwindow* const
	                  , const int _key
	                  , [[maybe_unused]] const int _scancode
	                  , const int _action
	                  , [[maybe_unused]] const int _mods) noexcept {
		auto& io = ImGui::GetIO();
		[[likely]] if (_action == GLFW_PRESS) {
			io.KeysDown[_key] = true;
		}
		else if (_action == GLFW_RELEASE) {
			io.KeysDown[_key] = false;
		}
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
#if SYS_WINDOWS
		io.KeySuper = false;
#else
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
#endif
	}

	void char_callback([[maybe_unused]] GLFWwindow* const, const unsigned _c) noexcept {
		ImGui::GetIO().AddInputCharacter(_c);
	}
} // namespace dce::platform // namespace dce::platform
