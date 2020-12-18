#include "native_config.hpp"

namespace dce::scripting {
	void map_to_sys_config(Config& _target, const NativeConfig& _in) noexcept {
		_target.display.is_full_screen = _in.Display_IsWindowFullscreen;
		_target.display.is_maximized = _in.Display_IsWindowMaximized;
		_target.display.width = _in.Display_WindowWidth;
		_target.display.height = _in.Display_WindowHeight;
		_target.display.vsync = _in.Display_VSync;
		_target.display.max_framerate = _in.Display_MaxFrameRate;

		_target.overlay.font_size = _in.Overlay_FontSize;
		_target.overlay.theme = static_cast<SystemTheme>(std::clamp(_in.Overlay_Theme, static_cast<CS_byte>(SystemTheme::DARK), static_cast<CS_byte>(SystemTheme::GREEN)));
		_target.overlay.enable_anti_aliasing = _in.Overlay_EnableFontAntialiasing;
		_target.overlay.alpha = _in.Overlay_Alpha;
		_target.overlay.rounding = _in.Overlay_Rounding;
		_target.overlay.show_terminal = _in.Overlay_ShowTerminal;
		_target.overlay.show_stats = _in.Overlay_ShowStats;

		_target.graphics.msaa_mode = static_cast<MsaaMode>(std::clamp(_in.Graphics_MSAAMode, static_cast<CS_byte>(MsaaMode::OFF), static_cast<CS_byte>(MsaaMode::X16)));
		_target.graphics.enable_high_dpi_mode = _in.Graphics_EnableHighDPIMode;
		_target.graphics.enable_srgb_backbuffer = _in.Graphics_EnableSRGBBackbuffer;
		_target.graphics.enable_hdr10 = _in.Graphics_EnableHDR10;
		_target.graphics.enable_max_anisotropy = _in.Graphics_EnableMaxAnisotropy;
	}
}