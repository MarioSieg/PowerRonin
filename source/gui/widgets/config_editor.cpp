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

#include "config_editor.hpp"
#include "../gui_headers.hpp"
#include "../font_headers.hpp"
#include "../window_names.hpp"

using namespace ImGui;

namespace dce::gui::widgets {
	void ConfigEditor::update(bool& _show, Config& _cfg, Scenery::Configuration& _scenery_config) const {
		SetNextWindowSize({300, 800}, ImGuiCond_FirstUseEver);
		[[likely]] if (Begin(CONFIG_EDITOR_NAME, &_show)) {
			if (CollapsingHeader(ICON_FA_ADJUST " Lighting", ImGuiTreeNodeFlags_DefaultOpen)) {
				ColorEdit3("Constant Ambient Color", value_ptr(_scenery_config.lighting.const_ambient_color)
				           , ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
			}
			if (CollapsingHeader(ICON_FA_SUN_CLOUD " Sun", ImGuiTreeNodeFlags_DefaultOpen)) {
				SliderFloat("Latitude", &_scenery_config.lighting.sun.latitude, .20f, 100.f);
				[[likely]] if (!_scenery_config.lighting.sun.sync_hour_with_env_time) {
					SliderFloat("Hour", &_scenery_config.lighting.sun.hour, 0, 24);
				}
				Checkbox("Use Scenery Time", &_scenery_config.lighting.sun.sync_hour_with_env_time);
				ColorEdit3("Sunlight Color", value_ptr(_scenery_config.lighting.sun.color)
				           , ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
			}
		}
		End();
	}
}
