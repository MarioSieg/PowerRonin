// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: config.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#pragma once

#include "serial.hpp"
#include <cstdint>

namespace dce {
	enum class SystemStyle {
		DARK
		, LIGHT
		, CHERRY
		, BLUE
		, GREEN
		,
	};

	enum class GraphicsBackend {
		AUTO
		, DIRECT3D11
		, DIRECT3D12
		, METAL
		, OPEN_GL
		, VULKAN
	};

	class Config : ISerializable {
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
			std::uint8_t font_size = 18;
			SystemStyle style = SystemStyle::DARK;
			bool enable_antialiasing = true;
			float transparency = 1.F;
			float rounding = .0F;
		} overlay;

		virtual auto serialize(JsonStream & /*j*/) const -> bool override;
		virtual auto deserialize(const JsonStream & /*j*/) -> bool override;
	};
} // namespace dce // namespace dce
