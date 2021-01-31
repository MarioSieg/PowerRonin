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

#include "gl_headers.hpp"
#include <cstdint>

namespace PowerRonin
{
	class RenderData;
}

struct ImDrawData;
struct ImFont;

namespace PowerRonin::Renderer
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
} // namespace PowerRonin::renderer // namespace PowerRonin::renderer
