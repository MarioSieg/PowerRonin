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

#include <cstddef>

namespace dce {
	class Diagnostics final {
	public:
		struct {
			std::size_t max_vram = 0;
			std::size_t used_vram = 0;

			std::size_t max_draw_calls = 0;
			std::size_t used_draw_calls = 0;

			std::size_t max_blit_calls = 0;
			std::size_t used_blit_calls = 0;

			std::size_t max_textures = 0;
			std::size_t used_textures = 0;

			std::size_t max_shaders = 0;
			std::size_t used_shaders = 0;

			std::size_t max_programs = 0;
			std::size_t used_programs = 0;

			std::size_t max_uniforms = 0;
			std::size_t used_uniforms = 0;

			std::size_t max_vertex_buffers = 0;
			std::size_t used_vertex_buffers = 0;

			std::size_t max_index_buffers = 0;
			std::size_t used_index_buffers = 0;

			std::size_t max_dynamic_vertex_buffers = 0;
			std::size_t used_dynamic_vertex_buffers = 0;

			std::size_t max_dynamic_index_buffers = 0;
			std::size_t used_dynamic_index_buffers = 0;

			std::size_t max_frame_buffers = 0;
			std::size_t used_frame_buffers = 0;
		} graphics;
	};
} // namespace dce // namespace dce
