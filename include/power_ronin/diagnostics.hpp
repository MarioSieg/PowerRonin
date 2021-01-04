#pragma once

#include <cstddef>

namespace power_ronin
{
	class Diagnostics final
	{
	public:
		struct
		{
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

			std::size_t scenery_mesh_drawcalls = 0;
		} graphics;
	};
} // namespace power_ronin // namespace power_ronin
