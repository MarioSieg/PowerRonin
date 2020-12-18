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

#pragma once

#include "../../include/dce/config.hpp"
#include "cstypes.hpp"

namespace dce::scripting {
	enum class NativeConfigApplyFlags: std::uint8_t {
		NONE = 0,
		DISPLAY= 1 << 0,
		OVERLAY = 1 << 1,
		GRAPHICS = 1 << 2,
	};
	
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
