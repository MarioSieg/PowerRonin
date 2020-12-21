#include "hierarchy.hpp"
#include "../gui_headers.hpp"
#include "../../../include/dce/entity_meta.hpp"
#include "../window_names.hpp"

using namespace ImGui;

namespace dce::gui::widgets {
	void Hierarchy::update(bool& _show, Registry& _registry) {
		SetNextWindowSize({300, 800}, ImGuiCond_FirstUseEver);
		if (Begin(HIERARCHY_NAME, &_show)) {
			const auto footer_height_to_reserve = GetStyle().ItemSpacing.y + GetFrameHeightWithSpacing();
			if (BeginChild("", {.0, -footer_height_to_reserve}, false)) {
				_registry.view<MetaData>().each([this](const ERef _ref, MetaData& _meta) {
					[[unlikely]] if (Button(_meta.name.c_str())) {
						this->selected_ = _ref;
					}
				});
				EndChild();
			}
		}
		End();
	}

	auto Hierarchy::get_selected() const noexcept -> ERef {
		return this->selected_;
	}
}
