// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: input.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "input.hpp"
#include "callback_hooks.hpp"
#include "platform_headers.hpp"
#include "../gui/gui_headers.hpp"
#include <limits>

#define HAS_NEW_CURSORS (GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3400)
#define MAP_BUTTON(NAV_NO, BUTTON_NO)       { if (buttons_count > (BUTTON_NO) && buttons[BUTTON_NO] == GLFW_PRESS) io.NavInputs[NAV_NO] = 1.0f; }
#define MAP_ANALOG(NAV_NO, AXIS_NO, V0, V1) { float v = (axes_count > (AXIS_NO)) ? axes[AXIS_NO] : (V0); v = (v - (V0)) / ((V1) - (V0)); if (v > 1.0f) v = 1.0f; if (io.NavInputs[NAV_NO] < v) io.NavInputs[NAV_NO] = v; }

namespace dce::platform {
	extern void* WINDOW_HANDLE;
} // namespace dce::platform

namespace dce::platform {
	auto GuiInput::initialize() -> bool {
		if (WINDOW_HANDLE == nullptr) {
			return false;
		}

		MOUSE_STATES = &this->mouse_buttons;
		this->window = WINDOW_HANDLE;

		auto& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.BackendPlatformName = "Dreamcast Engine";

		// Keyboard mapping:
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		//io.SetClipboardTextFn = ImGui_ImplGlfw_SetClipboardText;
		//io.GetClipboardTextFn = ImGui_ImplGlfw_GetClipboardText;
		//io.ClipboardUserData = g_Window;

		this->cursors[ImGuiMouseCursor_Arrow] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		this->cursors[ImGuiMouseCursor_TextInput] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		this->cursors[ImGuiMouseCursor_ResizeNS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		this->cursors[ImGuiMouseCursor_ResizeEW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
		this->cursors[ImGuiMouseCursor_Hand] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);

#if HAS_NEW_CURSORS

		this->cursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);
		this->cursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
		this->cursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
		this->cursors[ImGuiMouseCursor_NotAllowed] = glfwCreateStandardCursor(GLFW_NOT_ALLOWED_CURSOR);

#else

		this->cursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		this->cursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		this->cursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		this->cursors[ImGuiMouseCursor_NotAllowed] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);

#endif
		this->install_callback_procedures();

		return true;
	}

	void GuiInput::update() {
		int w = 0;
		int h = 0;
		int display_w = 0;
		int display_h = 0;
		glfwGetWindowSize(static_cast<GLFWwindow*>(this->window), &w, &h);
		glfwGetFramebufferSize(static_cast<GLFWwindow*>(this->window), &display_w, &display_h);
		auto& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(static_cast<float>(w), static_cast<float>(h));
		io.DisplayFramebufferScale = ImVec2(static_cast<float>(display_w) / w, static_cast<float>(display_h) / h);

		// Calculate time:
		const auto current_time = glfwGetTime();
		io.DeltaTime = timer > 0.0 ? static_cast<float>(current_time - timer) : static_cast<float>(1.F / 60.F);
		timer = current_time;
		this->update_mouse();
		this->update_cursor();
		update_gamepads();
	}

	void GuiInput::update_mouse() {
		auto* const win = static_cast<GLFWwindow*>(this->window);
		auto& io = ImGui::GetIO();

		for (std::size_t i = 0; i < sizeof io.MouseDown / sizeof *io.MouseDown; i++) {
			io.MouseDown[i] = this->mouse_buttons[i] || glfwGetMouseButton(win, i) != 0;
			this->mouse_buttons[i] = false;
		}

		// Update mouse position:
		const ImVec2 mouse_pos_backup = io.MousePos;
		io.MousePos = ImVec2(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());

		const bool focused = glfwGetWindowAttrib(win, GLFW_FOCUSED) != 0;

		if (focused) {
			if (io.WantSetMousePos) {
				glfwSetCursorPos(win, static_cast<double>(mouse_pos_backup.x), static_cast<double>(mouse_pos_backup.y));
			}
			else {
				double mouse_x = NAN;
				double mouse_y = NAN;
				glfwGetCursorPos(win, &mouse_x, &mouse_y);
				io.MousePos = ImVec2(static_cast<float>(mouse_x), static_cast<float>(mouse_y));
			}
		}
	}

	void GuiInput::update_cursor() {
		auto* const win = static_cast<GLFWwindow*>(this->window);
		auto& io = ImGui::GetIO();
		if ((io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) != 0 || glfwGetInputMode(win, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
			return;
		}

		const auto gui_mouse_cursor = ImGui::GetMouseCursor();
		if (gui_mouse_cursor == ImGuiMouseCursor_None || io.MouseDrawCursor) {
			// Hide OS mouse cursor if imgui is drawing it or if it wants no cursor:
			glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		else {
			// Show OS mouse cursor:
			glfwSetCursor(win, this->cursors[gui_mouse_cursor] != nullptr ? this->cursors[gui_mouse_cursor] : this->cursors[ImGuiMouseCursor_Arrow]);
			glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	void GuiInput::update_gamepads() {
		ImGuiIO& io = ImGui::GetIO();

		memset(io.NavInputs, 0, sizeof io.NavInputs);

		if ((io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad) != 0) {
			return;
		}

		auto axes_count = 0;
		auto buttons_count = 0;
		const float* const axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
		const unsigned char* const buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttons_count);
		MAP_BUTTON(ImGuiNavInput_Activate, 0) // Cross / A
		MAP_BUTTON(ImGuiNavInput_Cancel, 1) // Circle / B
		MAP_BUTTON(ImGuiNavInput_Menu, 2) // Square / X
		MAP_BUTTON(ImGuiNavInput_Input, 3) // Triangle / Y
		MAP_BUTTON(ImGuiNavInput_DpadLeft, 13) // D-Pad Left
		MAP_BUTTON(ImGuiNavInput_DpadRight, 11) // D-Pad Right
		MAP_BUTTON(ImGuiNavInput_DpadUp, 10) // D-Pad Up
		MAP_BUTTON(ImGuiNavInput_DpadDown, 12) // D-Pad Down
		MAP_BUTTON(ImGuiNavInput_FocusPrev, 4) // L1 / LB
		MAP_BUTTON(ImGuiNavInput_FocusNext, 5) // R1 / RB
		MAP_BUTTON(ImGuiNavInput_TweakSlow, 4) // L1 / LB
		MAP_BUTTON(ImGuiNavInput_TweakFast, 5) // R1 / RB
		MAP_ANALOG(ImGuiNavInput_LStickLeft, 0, -0.3F, -0.9F)
		MAP_ANALOG(ImGuiNavInput_LStickRight, 0, +0.3F, +0.9F)
		MAP_ANALOG(ImGuiNavInput_LStickUp, 1, +0.3F, +0.9F)
		MAP_ANALOG(ImGuiNavInput_LStickDown, 1, -0.3F, -0.9F)

		if (axes_count > 0 && buttons_count > 0) {
			io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
		}
		else {
			io.BackendFlags &= ~ImGuiBackendFlags_HasGamepad;
		}
	}

	void GuiInput::install_callback_procedures() const {
		auto* const win = static_cast<GLFWwindow*>(this->window);
		glfwSetMouseButtonCallback(win, &mouse_button_callback);
		glfwSetScrollCallback(win, &scroll_callback);
		glfwSetKeyCallback(win, &key_callback);
		glfwSetCharCallback(win, &char_callback);
	}

	void GuiInput::shutdown() {
		MOUSE_STATES = nullptr;
		for (auto*& cur : this->cursors) {
			if (cur == nullptr) {
				continue;
			}
			glfwDestroyCursor(cur);
			cur = nullptr;
		}
	}
} // namespace dce::platform // namespace dce::platform
