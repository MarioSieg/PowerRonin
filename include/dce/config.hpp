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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

#include "serial.hpp"
#include <cstdint>

namespace dce {
	enum class SystemTheme {
		DARK,
		LIGHT,
		CHERRY,
		BLUE,
		GREEN,
	};

	enum class GraphicsBackend {
		AUTO,
		DIRECT_3D11,
		DIRECT_3D12,
		METAL,
		OPEN_GL,
		VULKAN
	};

	class Config final : ISerializable {
	public:
		struct {
			GraphicsBackend backend_api = GraphicsBackend::AUTO;
		} graphics;

		struct {
			std::uint16_t width = 1920;
			std::uint16_t height = 1080;
			bool full_screen = false;
			bool maximize = true;
		} display;

		struct {
			std::uint8_t font_size = 24;
			SystemTheme theme = SystemTheme::DARK;
			bool enable_antialiasing = true;
			float transparency = 1.5F;
			float rounding = 4.F;
		} overlay;

		virtual void serialize(JsonStream& _j) const override;
		virtual void deserialize(const JsonStream& _j) override;
	};
} // namespace dce // namespace dce
