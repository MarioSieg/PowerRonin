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

#pragma once

#include "serial.hpp"
#include "csinterop.hpp"

#include <cstdint>

namespace power_ronin
{
	CS_HYBRID_INTEROP("Dreamcast.Core.GraphicsAPI")

	enum class GraphicsBackend: std::uint8_t
	{
		DIRECT_3D11 = 0,
		DIRECT_3D12 = 1,
		METAL = 2,
		OPEN_GL = 3,
		VULKAN = 4
	};

	CS_HYBRID_INTEROP("Dreamcast.Core.MsaaMode")

	enum class MsaaMode: std::uint8_t
	{
		OFF = 1,
		X2 = 2,
		X4 = 4,
		X8 = 8,
		X16 = 16
	};

	CS_HYBRID_INTEROP("Dreamcast.Core.DisplayConfig")

	struct DisplayConfig final
	{
		CS_bool is_full_screen;
		CS_bool is_maximized;
		CS_Size2 resolution;
		CS_bool vsync;
		CS_ushort max_framerate;
	};

	CS_HYBRID_INTEROP("Dreamcast.Core.EditorConfig")

	struct EditorConfig final
	{
		CS_byte custom_font_size;
		CS_byte auto_font_size_fhd;
		CS_byte auto_font_size_whqh;
		CS_byte auto_font_size_uhd;
		CS_bool enable_auto_font_size;
		CS_bool enable_font_anti_aliasing;
		CS_float alpha;
		CS_float rounding;
		CS_bool show_terminal;
		CS_bool show_stats;
		CS_bool show_matrix_stats;
		CS_byte stats_text_color;
		CS_bool show_big_stats;
		CS_bool show_grid;
		CS_float grid_size;
		CS_Vector3 grid_origin_center;
		CS_bool show_gizmos;
	};

	CS_HYBRID_INTEROP("Dreamcast.Core.EditorConfig")

	struct GraphicsConfig final
	{
		GraphicsBackend graphics_api;
		MsaaMode msaa_mode;
		bool enable_high_dpi_mode;
		bool enable_srgb_mode;
		bool enable_hdr10;
		bool enable_max_anisotropy;
	};

	struct Scripting final
	{
		std::filesystem::path config_dir = "runtime/etc";
		std::filesystem::path library_dir = "runtime/lib";
	};

	struct App final
	{
		std::string app_name = {};
		std::string app_company = {};
	};

	class Config final
	{
	public:
		DisplayConfig display;

		EditorConfig editor;

		GraphicsConfig graphics;

		Scripting scripting;

		App app;
	};
} // namespace power_ronin // namespace power_ronin
