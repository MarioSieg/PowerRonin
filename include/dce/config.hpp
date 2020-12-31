#pragma once

#include "serial.hpp"
#include <cstdint>

#include "mathtypes.hpp"

namespace dce {
	enum class SystemTheme {
		DARK = 0,
		LIGHT = 1,
		CHERRY = 2,
		BLUE = 3,
		GREEN = 4,
	};

	enum class GraphicsBackend {
		AUTO,
		DIRECT_3D11,
		DIRECT_3D12,
		METAL,
		OPEN_GL,
		VULKAN
	};

	enum class MsaaMode: std::uint8_t {
		OFF = 1,
		X2 = 2,
		X4 = 4,
		X8 = 8,
		X16 = 16
	};

	class Config final {
	public:
		struct Display final {
			std::uint16_t width = 1920;
			std::uint16_t height = 1080;
			bool is_full_screen = false;
			bool is_maximized = true;
			bool vsync = false;
			std::uint16_t max_framerate = 300;
		} display;

		struct Editor final {
			std::uint8_t font_size = 24;
			std::uint8_t auto_font_size_fhd = 14;
			std::uint8_t auto_font_size_whqh = 18;
			std::uint8_t auto_font_size_uhd = 22;
			bool auto_font_size = true;
			SystemTheme theme = SystemTheme::DARK;
			bool enable_font_anti_aliasing = true;
			float alpha = 1.F;
			float rounding = 4.F;
			bool show_terminal = true;
			bool show_stats = true;
			bool show_grid = true;
			float grid_size = 10.f;
			SimdVector3<> grid_origin = { 0, 0, 0 };
			bool enable_gizmos = true;
		} editor;

		struct Graphics final {
			GraphicsBackend backend_api = GraphicsBackend::AUTO;
			MsaaMode msaa_mode = MsaaMode::OFF;
			bool enable_high_dpi_mode = false;
			bool enable_srgb_backbuffer = true;
			bool enable_hdr10 = false;
			bool enable_max_anisotropy = true;
		} graphics;

		struct Scripting final {
			std::filesystem::path config_dir = "runtime/etc";
			std::filesystem::path library_dir = "runtime/lib";
		} scripting;

		struct App final {
			std::string app_name = {};
			std::string app_company = {};
		} app;
	};
} // namespace dce // namespace dce
