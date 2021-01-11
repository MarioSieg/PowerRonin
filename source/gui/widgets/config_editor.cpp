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

#include "config_editor.hpp"
#include "../gui_headers.hpp"
#include "../font_headers.hpp"
#include "../utils.hpp"
#include "../window_names.hpp"

using namespace ImGui;

namespace power_ronin::gui::widgets
{
	void ConfigEditor::update(bool& _show, Config& _cfg, Scenery::Configuration& _scenery_config) const
	{
		SetNextWindowSize({300, 800}, ImGuiCond_FirstUseEver);
		if (Begin(CONFIG_EDITOR_NAME, &_show)) [[likely]]
		{
			if (CollapsingHeader(ICON_FA_SUN_CLOUD " Scenery", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
			{
				ColorEdit3("Constant Ambient Color", value_ptr(_scenery_config.lighting.const_ambient_color), ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
				SliderFloat("Latitude", &_scenery_config.lighting.sun.latitude, .20f, 100.f);
				if (!_scenery_config.lighting.sun.sync_hour_with_env_time) [[likely]]
				{
					SliderFloat("Hour", &_scenery_config.lighting.sun.hour, 0, 24);
				}
				Checkbox("Use Scenery Time", &_scenery_config.lighting.sun.sync_hour_with_env_time);
				ColorEdit3("Sunlight Color", value_ptr(_scenery_config.lighting.sun.color), ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
			}
			if (CollapsingHeader(ICON_FA_TV " Display", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
			{
				Checkbox("Full Screen", &_cfg.display.is_full_screen);
				Checkbox("Maximized", &_cfg.display.is_maximized);
				int resolution[2] = {
					static_cast<int>(_cfg.display.resolution.width),
					static_cast<int>(_cfg.display.resolution.height)
				};
				InputInt2("Resolution", resolution);
				_cfg.display.resolution.width = std::clamp<decltype(_cfg.display.resolution.width)>(resolution[0], 800, std::numeric_limits<std::uint16_t>::max());
				_cfg.display.resolution.height = std::clamp<decltype(_cfg.display.resolution.height)>(resolution[1], 600, std::numeric_limits<std::uint16_t>::max());
				Checkbox("VSync", &_cfg.display.vsync);
				input_integer("Max FPS", _cfg.display.max_framerate);
			}
			if (CollapsingHeader(ICON_FA_BRUSH " Editor", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
			{
				slider_integer("Custom Font Size", _cfg.editor.custom_font_size, 10, 28);
				Checkbox("User Auto Font Size", &_cfg.editor.enable_auto_font_size);
				if (_cfg.editor.enable_auto_font_size) [[likely]]
				{
					slider_integer("Auto Font Size Full HD", _cfg.editor.auto_font_size_fhd, 10, 28);
					slider_integer("Auto Font Size Wide Quad HD", _cfg.editor.auto_font_size_whqh, 10, 28);
					slider_integer("Auto Font Size Ultra HD 4K", _cfg.editor.auto_font_size_uhd, 10, 28);
				}
				Checkbox("Font Antialiasing", &_cfg.editor.enable_font_anti_aliasing);
				SliderFloat("UI Transparency", &_cfg.editor.alpha, .1f, 1.f);
				SliderFloat("UI Rounding", &_cfg.editor.rounding, .0f, 10.f);
				Checkbox("Show Terminal On Startup", &_cfg.editor.show_terminal);
				Checkbox("Show Gizmos", &_cfg.editor.show_gizmos);
				Checkbox("Show Stats", &_cfg.editor.show_stats);
				Checkbox("Show Matrix Stats", &_cfg.editor.show_matrix_stats);
				Checkbox("Big Stats Font", &_cfg.editor.show_big_stats);
				float col[3] = {};
				ColorEdit3("Stats Text Color", col);
				Checkbox("Show Grid", &_cfg.editor.show_grid);
				DragFloat("Grid Size", &_cfg.editor.grid_size, 1.f, 10000.f);
				DragFloat3("Grid Center", &_cfg.editor.grid_origin_center.x);
			}
			if (CollapsingHeader(ICON_FA_IMAGE " Graphics", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
			{
				Checkbox("High DPI Mode", &_cfg.graphics.enable_high_dpi_mode);
				Checkbox("SRGB Mode", &_cfg.graphics.enable_srgb_mode);
				Checkbox("HRD10 Rendering", &_cfg.graphics.enable_hdr10);
				Checkbox("Max Anisotropy", &_cfg.graphics.enable_max_anisotropy);
			}
		}
		End();
	}
}

#endif
