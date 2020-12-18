#pragma once

#include "../../include/dce/config.hpp"
#include "cstypes.hpp"

namespace dce::scripting {
	/// <summary>
	/// !! Maps to NativeConfig in NativeConfig.cs !!
	/// </summary>
	struct NativeConfig final {
		CS_bool Display_IsWindowFullscreen;
		CS_bool Display_IsWindowMaximized;
		CS_ushort Display_WindowWidth;
		CS_ushort Display_WindowHeight;
		CS_bool Display_VSync;
		CS_ushort Display_MaxFrameRate;
		
		CS_byte Overlay_FontSize;
		CS_byte Overlay_Theme;
		CS_bool Overlay_EnableFontAntialiasing;
		CS_float Overlay_Alpha;
		CS_float Overlay_Rounding;
		CS_bool Overlay_ShowTerminal;
		CS_bool Overlay_ShowStats;
		
		CS_byte Graphics_MSAAMode;
		CS_bool Graphics_EnableHighDPIMode;
		CS_bool Graphics_EnableSRGBBackbuffer;
		CS_bool Graphics_EnableHDR10;
		CS_bool Graphics_EnableMaxAnisotropy;
	};

	extern void map_to_sys_config(Config& _target, const NativeConfig& _in) noexcept;
}
