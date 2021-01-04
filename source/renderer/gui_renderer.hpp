#pragma once

#include "gl_headers.hpp"
#include <cstdint>

namespace power_ronin
{
	class RenderData;
}

struct ImDrawData;
struct ImFont;

namespace power_ronin::renderer
{
	class GuiRenderer final
	{
	public:
		auto initialize(std::uint8_t _font_size) -> bool;
		void render(const ImDrawData* _data) const;
		void shutdown() const;

	private:
		ImFont* font_ = nullptr;
		bgfx::VertexLayout layout = {};
		bgfx::ProgramHandle gui_program_ = {bgfx::kInvalidHandle};
		bgfx::ProgramHandle gui_image_program_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle texture_uniform_ = {bgfx::kInvalidHandle};
		bgfx::TextureHandle texture_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle image_lod_enabled_ = {bgfx::kInvalidHandle};
	};
} // namespace power_ronin::renderer // namespace power_ronin::renderer
