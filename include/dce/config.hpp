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

#include "serial.hpp"
#include <cstdint>

namespace dce {
	enum class SystemTheme {
		DARK = 0
		, LIGHT = 1
		, CHERRY = 2
		, BLUE = 3
		, GREEN = 4
		,
	};

	enum class GraphicsBackend {
		AUTO
		, DIRECT_3D11
		, DIRECT_3D12
		, METAL
		, OPEN_GL
		, VULKAN
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
		struct {
			std::uint16_t width = 1920;
			std::uint16_t height = 1080;
			bool is_full_screen = false;
			bool is_maximized = true;
			bool vsync = false;
			std::uint16_t max_framerate = 300;
		} display;

		struct {
			std::uint8_t font_size = 24;
			SystemTheme theme = SystemTheme::DARK;
			bool enable_anti_aliasing = true;
			float alpha = 1.F;
			float rounding = 4.F;
			bool show_terminal = true;
			bool show_stats = true;
		} overlay;

		struct {
			GraphicsBackend backend_api = GraphicsBackend::AUTO;
			MsaaMode msaa_mode = MsaaMode::X2;
			bool enable_high_dpi_mode = false;
			bool enable_srgb_backbuffer = true;
			bool enable_hdr10 = false;
			bool enable_max_anisotropy = true;
		} graphics;

		struct {
			std::uint16_t max_channels = 2048;
		} audio;

		struct {
			std::filesystem::path config_dir = "extern/mono/etc";
			std::filesystem::path library_dir = "extern/mono/lib";
		} scripting;

		struct {
			std::string app_name = {};
			std::string app_company = {};
		} app;
	};
} // namespace dce // namespace dce
