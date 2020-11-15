// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: imgui_renderer.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#pragma once

#include "bgfx_headers.hpp"
#include <cstdint>

struct ImDrawData;
struct ImFont;

namespace dce::renderer {
	class GuiRenderer final {
	public:
		static constexpr std::uint16_t VIEW_ID = 0xFF;

		auto initialize(std::uint8_t font_size) -> bool;
		void render(const ImDrawData *data) const;
		void shutdown() const;

	private:
		ImFont *font = nullptr;
		bgfx::VertexLayout layout = {};
		bgfx::ProgramHandle gui_program = {bgfx::kInvalidHandle};
		bgfx::ProgramHandle gui_image_program = {bgfx::kInvalidHandle};
		bgfx::UniformHandle texture_uniform = {bgfx::kInvalidHandle};
		bgfx::TextureHandle texture = {bgfx::kInvalidHandle};
		bgfx::UniformHandle image_lod_enabled = {bgfx::kInvalidHandle};
	};
} // namespace dce::renderer // namespace dce::renderer
