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
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../../include/dce/input.hpp"
#include "gui/gui_headers.hpp"

namespace dce {
	auto Input::is_key_down(const Key _key) const noexcept -> bool {
		return ImGui::GetIO().KeysDown[static_cast<std::size_t>(_key)];
	}

	auto Input::is_mouse_button_down(const MouseButton _mb) const noexcept -> bool {
		return ImGui::IsMouseDown(static_cast<ImGuiMouseButton>(_mb));
	}

	auto Input::get_mouse_position() const noexcept -> Vector2<> {
		const auto position = ImGui::GetMousePos();
		return {position.x, position.y};
	}
}
