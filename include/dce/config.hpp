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
		DARK
		, LIGHT
		, CHERRY
		, BLUE
		, GREEN
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

	class Config final : ISerializable {
	public:
		struct {
			GraphicsBackend backend_api = GraphicsBackend::AUTO;
		} graphics;

		struct {
			std::uint16_t width = 1920;
			std::uint16_t height = 1080;
			bool is_full_screen = false;
			bool is_maximized = true;
		} display;

		struct {
			std::uint8_t font_size = 24;
			SystemTheme theme = SystemTheme::DARK;
			bool enable_anti_aliasing = true;
			float transparency = 1.F;
			float rounding = 4.F;
			bool show_terminal = true;
			bool show_stats = true;
		} overlay;

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
			std::filesystem::path splash_image = "textures/splash/splash.png";
		} app;

		virtual void serialize(JsonStream& _j) const override;
		virtual void deserialize(const JsonStream& _j) override;
	};
} // namespace dce // namespace dce
