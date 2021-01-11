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

#if AUTO_TEC

#include "scenery_viewer.hpp"
#include "../gui_headers.hpp"
#include "../window_names.hpp"
#include "../../include/power_ronin/renderer_data.hpp"

using namespace ImGui;

namespace power_ronin::gui::widgets
{
	void SceneryViewer::update(bool& _show, RenderData& _data) const
	{
		if (Begin(SCENERY_VIEWER_NAME, &_show, ImGuiWindowFlags_NoBackground)) [[likely]]
		{
			const auto window_size = GetWindowSize();
			const auto window_pos = GetWindowPos();
			constexpr auto title_offset = 25;
			_data.primary_viewport.x = window_size.x;
			_data.primary_viewport.y = window_size.y - title_offset;
			_data.scenery_viewport_position.x = window_pos.x;
			_data.scenery_viewport_position.y = window_pos.y + title_offset;
		}
		End();
	}
}

#endif
