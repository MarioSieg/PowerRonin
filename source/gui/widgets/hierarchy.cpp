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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "hierarchy.hpp"
#include "../gui_headers.hpp"
#include "../font_headers.hpp"
#include "../../../include/dce/entity_meta.hpp"

using namespace ImGui;

namespace dce::gui::widgets {
	void Hierarchy::update(bool& _show, Registry& _registry) {
		SetNextWindowSize({300, 800}, ImGuiCond_FirstUseEver);
		if (Begin(ICON_FA_SITEMAP " Hierarchy", &_show)) {
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
