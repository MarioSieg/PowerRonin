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

#include "scenery_viewer.hpp"
#include "../gui_headers.hpp"
#include "../font_headers.hpp"
#include "../window_names.hpp"
#include "../../include/dce/renderer_data.hpp"

using namespace ImGui;

namespace dce::gui::widgets {
	void SceneryViewer::update(bool& _show, RenderData& _data) const {
		[[likely]] if (Begin(SCENERY_VIEWER_NAME, &_show, ImGuiWindowFlags_NoBackground)) {
			const auto window_size = GetWindowSize();
			const auto window_pos = GetWindowPos();
			_data.scenery_viewport_size.x = window_size.x;
			_data.scenery_viewport_size.y = window_size.y;
			_data.scenery_viewport_position.x = window_pos.x;
			_data.scenery_viewport_position.y = window_pos.y;
		}
		End();
	}
}
