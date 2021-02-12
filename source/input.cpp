#include "../../Include/PowerRonin/Input.hpp"
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
