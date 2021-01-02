#pragma once

#include "serial.hpp"
#include "mathtypes.hpp"
#include "csinterop.hpp"

#include <cstdint>

namespace dce
{
	enum class SystemTheme
	{
		DARK = 0,
		LIGHT = 1,
		CHERRY = 2,
		BLUE = 3,
		GREEN = 4,
	};

	enum class GraphicsBackend
	{
		AUTO,
		DIRECT_3D11,
		DIRECT_3D12,
		METAL,
		OPEN_GL,
		VULKAN
	};

	enum class MsaaMode: std::uint8_t
	{
		OFF = 1,
		X2 = 2,
		X4 = 4,
		X8 = 8,
		X16 = 16
	};

	CS_HYBRID_INTEROP("Dreamcast.Core.Configuration.DisplayConfiguration")
	struct DisplayConfiguration final
	{
		CS_ushort width;
		CS_ushort height;
		CS_bool is_full_screen;
		CS_bool is_maximized;
		CS_bool vsync;
		CS_ushort max_framerate;
	};

	CS_HYBRID_INTEROP("Dreamcast.Core.Configuration.EditorConfiguration")
	struct EditorConfiguration final
	{
		CS_byte font_size;
		CS_byte auto_font_size_fhd;
		CS_byte auto_font_size_whqh;
		CS_byte auto_font_size_uhd;
		CS_bool auto_font_size;
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
		CS_bool enable_gizmos;
	};

	struct Graphics final
	{
		GraphicsBackend backend_api = GraphicsBackend::AUTO;
		MsaaMode msaa_mode = MsaaMode::OFF;
		bool enable_high_dpi_mode = false;
		bool enable_srgb_backbuffer = true;
		bool enable_hdr10 = false;
		bool enable_max_anisotropy = true;
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
		DisplayConfiguration display;

		EditorConfiguration editor;

		Graphics graphics;

		Scripting scripting;

		App app;
	};
} // namespace dce // namespace dce
