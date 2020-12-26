#include "scenery_viewer.hpp"
#include "../gui_headers.hpp"
#include "../window_names.hpp"
#include "../../include/dce/renderer_data.hpp"

using namespace ImGui;

namespace dce::gui::widgets {
	void SceneryViewer::update(bool& _show, RenderData& _data) const {
		[[likely]] if (Begin(SCENERY_VIEWER_NAME, &_show, ImGuiWindowFlags_NoBackground)) {
			const auto window_size = GetWindowSize();
			const auto window_pos = GetWindowPos();
			constexpr auto title_offset = 25;
			_data.scenery_viewport_size.x = window_size.x;
			_data.scenery_viewport_size.y = window_size.y - title_offset;
			_data.scenery_viewport_position.x = window_pos.x;
			_data.scenery_viewport_position.y = window_pos.y + title_offset;
		}
		End();
	}
}
