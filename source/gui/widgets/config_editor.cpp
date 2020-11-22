// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: config_editor.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 22.11.2020 00:50

#include "config_editor.hpp"
#include "../gui_headers.hpp"
#include "../font_headers.hpp"

using namespace ImGui;

namespace dce::gui::widgets {

	void ConfigEditor::update(bool &_show, Config &_cfg, Scenery::Configuration &_scenery_config) const {
		SetNextWindowSize({300, 800}, ImGuiCond_FirstUseEver);
		[[likely]] if (Begin(ICON_FA_COGS " Configuration", &_show)) {
			if (CollapsingHeader(ICON_FA_LIGHTBULB " Lighting")) {
				ColorPicker3("Constant Ambient Color", value_ptr(_scenery_config.lighting.const_ambient_color)
				             , ImGuiColorEditFlags_PickerHueWheel);
			}
			if (CollapsingHeader(ICON_FA_SUN " Sun")) {
				SliderFloat("Latitude", &_scenery_config.lighting.sun.latitude, .20f, 100.f);
				[[likely]] if (!_scenery_config.lighting.sun.sync_hour_with_env_time) {
					SliderFloat("Hour", &_scenery_config.lighting.sun.hour, 0, 24);
				}
				Checkbox("Use Scenery Time", &_scenery_config.lighting.sun.sync_hour_with_env_time);
				ColorPicker3("Sunlight Color", value_ptr(_scenery_config.lighting.sun.color)
				             , ImGuiColorEditFlags_PickerHueWheel);
			}
		}
		End();
	}
}
