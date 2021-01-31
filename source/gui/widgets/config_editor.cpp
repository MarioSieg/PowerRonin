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

namespace PowerRonin::Interface::widgets
{
	void ConfigEditor::update(bool& _show, SystemConfig& _cfg, Scenery::Configuration& _scenery_config) const
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
				Checkbox("Full Screen", &_cfg.Display.IsFullScreen);
				Checkbox("Maximized", &_cfg.Display.IsMaximized);
				int resolution[2] = {
					static_cast<int>(_cfg.Display.Resolution.Width),
					static_cast<int>(_cfg.Display.Resolution.Height)
				};
				InputInt2("Resolution", resolution);
				_cfg.Display.Resolution.Width = std::clamp<decltype(_cfg.Display.Resolution.Width)>(resolution[0], 800, std::numeric_limits<std::uint16_t>::max());
				_cfg.Display.Resolution.Height = std::clamp<decltype(_cfg.Display.Resolution.Height)>(resolution[1], 600, std::numeric_limits<std::uint16_t>::max());
				Checkbox("VSync", &_cfg.Display.VSync);
				input_integer("Max FPS", _cfg.Display.MaxFrameRate);
			}
			if (CollapsingHeader(ICON_FA_BRUSH " Editor", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
			{
				slider_integer("Custom Font Size", _cfg.Editor.CustomFontSize, 10, 28);
				Checkbox("User Auto Font Size", &_cfg.Editor.EnableAutoFontSize);
				if (_cfg.Editor.EnableAutoFontSize) [[likely]]
				{
					slider_integer("Auto Font Size Full HD", _cfg.Editor.AutoFontSizeFullHD, 10, 28);
					slider_integer("Auto Font Size Wide Quad HD", _cfg.Editor.AutoFontSizeWideQuadHD, 10, 28);
					slider_integer("Auto Font Size Ultra HD 4K", _cfg.Editor.AutoFontSizeUltraHD, 10, 28);
				}
				Checkbox("Font Antialiasing", &_cfg.Editor.EnableFontAntiAliasing);
				SliderFloat("UI Transparency", &_cfg.Editor.Alpha, .1f, 1.f);
				SliderFloat("UI Rounding", &_cfg.Editor.Rounding, .0f, 10.f);
				Checkbox("Show Terminal On Startup", &_cfg.Editor.ShowTerminal);
				Checkbox("Show Gizmos", &_cfg.Editor.ShowGizmos);
				Checkbox("Show Stats", &_cfg.Editor.ShowStats);
				Checkbox("Show Matrix Stats", &_cfg.Editor.ShowMatrixStats);
				Checkbox("Big Stats Font", &_cfg.Editor.ShowBigStats);
				float col[3] = {};
				ColorEdit3("Stats Text Color", col);
				Checkbox("Show Grid", &_cfg.Editor.ShowGrid);
				DragFloat("Grid Size", &_cfg.Editor.GridSize, 1.f, 10000.f);
				DragFloat3("Grid Center", &_cfg.Editor.GridOriginCenter.X);
			}
			if (CollapsingHeader(ICON_FA_IMAGE " Graphics", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
			{
				Checkbox("High DPI Mode", &_cfg.Graphics.EnableHighDpiMode);
				Checkbox("SRGB Mode", &_cfg.Graphics.EnableSrgbMode);
				Checkbox("HRD10 Rendering", &_cfg.Graphics.EnableHdr10);
				Checkbox("Max Anisotropy", &_cfg.Graphics.EnableMaxAnisotropy);
			}
		}
		End();
	}
}

#endif
