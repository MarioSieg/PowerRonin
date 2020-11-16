// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: hierarchy.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 16.11.2020 13:25

#include "hierarchy.hpp"
#include "../gui_headers.hpp"
#include "../font_headers.hpp"
#include "../../../include/dce/entity_meta.hpp"

using namespace ImGui;

namespace dce::gui::widgets {

	void Hierarchy::update(bool &_show, Registry &_registry) {
		SetNextWindowSize({300, 800}, ImGuiCond_FirstUseEver);
		if (Begin(ICON_FA_SITEMAP " Hierarchy", &_show)) {
			const auto footer_height_to_reserve = GetStyle().ItemSpacing.y + GetFrameHeightWithSpacing();
			if (BeginChild("", {.0, -footer_height_to_reserve}, false)) {
				_registry.view<CMetaData>().each([this](const ERef _ref, CMetaData &_meta) {
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
