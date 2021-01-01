#include "hierarchy.hpp"
#include "../gui_headers.hpp"
#include "../window_names.hpp"
#include "../../../include/dce/comcollections.hpp"

using namespace ImGui;

namespace dce::gui::widgets {
	void Hierarchy::update(bool& _show, Registry& _registry) {
		SetNextWindowSize({300, 800}, ImGuiCond_FirstUseEver);
		[[likely]] if (Begin(HIERARCHY_NAME, &_show)) {			
			const auto footer_height_to_reserve = GetStyle().ItemSpacing.y + GetFrameHeightWithSpacing();
			[[likely]] if (BeginChild("", {.0, -footer_height_to_reserve}, false)) {
				_registry.view<MetaData>().each([this](const ERef _ref, MetaData& _meta) {
					PushID(static_cast<int>(_ref));
					[[unlikely]] if (Selectable(_meta.name.c_str(), _ref == this->selected)) {
						this->selected = _ref;
					}
					PopID();
				});
				EndChild();
			}
		}
		End();
	}
}
