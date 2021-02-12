#if AUTO_TEC

#include "scenery_viewer.hpp"
#include "../gui_headers.hpp"
#include "../window_names.hpp"
#include "../../Include/PowerRonin/RenderState.hpp"

using namespace ImGui;

namespace PowerRonin::Interface::widgets
{
	void SceneryViewer::update(bool& _show, RenderState& _data) const
	{
		if (Begin(SCENERY_VIEWER_NAME, &_show, ImGuiWindowFlags_NoBackground)) [[likely]]
		{
			const auto window_size = GetWindowSize();
			const auto window_pos = GetWindowPos();
			constexpr auto title_offset = 25;
			_data.PrimaryViewport.x = window_pos.x;
			_data.PrimaryViewport.y = window_pos.y + title_offset;
			_data.PrimaryViewport.z = window_size.x;
			_data.PrimaryViewport.w = window_size.y - title_offset;
		}
		End();
	}
}

#endif
