// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#include "../../include/power_ronin/input.hpp"
#include "gui/gui_headers.hpp"

namespace PowerRonin
{
	auto Input::IsKeyDown(const Key key) const noexcept -> bool
	{
		return ImGui::GetIO().KeysDown[static_cast<std::size_t>(key)];
	}

	auto Input::IsMouseButtonDown(const MouseButton mouseButton) const noexcept -> bool
	{
		return ImGui::IsMouseDown(static_cast<ImGuiMouseButton>(mouseButton));
	}

	auto Input::MousePosition() const noexcept -> Vector2<>
	{
		const auto position = ImGui::GetMousePos();
		return {position.x, position.y};
	}
}
