// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: input.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 18.11.2020 13:27

#include "../../include/dce/input.hpp"
#include "gui/gui_headers.hpp"

namespace dce {

	auto Input::is_key_down(const Key _key) const noexcept -> bool {
		return ImGui::GetIO().KeysDown[static_cast<std::size_t>(_key)];
	}

	auto Input::is_mouse_button_down(const MouseButton _mb) const noexcept -> bool {
		return ImGui::IsMouseDown(static_cast<ImGuiMouseButton>(_mb));
	}

	auto Input::get_mouse_position() const noexcept -> Vec2 {
		const auto position = ImGui::GetMousePos();
		return {position.x, position.y};
	}
}
