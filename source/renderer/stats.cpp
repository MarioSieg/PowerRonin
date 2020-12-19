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

#include "stats.hpp"

#include "../../include/dce/runtime.hpp"
#include "../../extern/bgfx/bgfx/include/bgfx/bgfx.h"

namespace dce::renderer {
	void get_limits(Diagnostics& _diag) noexcept {
		const auto& limits = bgfx::getCaps()->limits;
		_diag.graphics.max_vram = bgfx::getStats()->gpuMemoryMax;
		_diag.graphics.max_draw_calls = limits.maxDrawCalls;
		_diag.graphics.max_blit_calls = limits.maxComputeBindings;
		_diag.graphics.max_textures = limits.maxTextures;
		_diag.graphics.max_shaders = limits.maxShaders;
		_diag.graphics.max_programs = limits.maxPrograms;
		_diag.graphics.max_uniforms = limits.maxUniforms;
		_diag.graphics.max_vertex_buffers = limits.maxVertexBuffers;
		_diag.graphics.max_index_buffers = limits.maxIndexBuffers;
		_diag.graphics.max_dynamic_vertex_buffers = limits.maxDynamicVertexBuffers;
		_diag.graphics.max_dynamic_index_buffers = limits.maxDynamicIndexBuffers;
		_diag.graphics.max_frame_buffers = limits.maxFrameBuffers;
	}

	void dump_limits(AsyncProtocol& _proto) {
		const auto* const caps = bgfx::getCaps();
		_proto.info("Supported flags: {:B}", caps->supported);
		_proto.info("Vendor ID: {}", caps->vendorId);
		_proto.info("Device ID: {}", caps->deviceId);
		_proto.info("(NDC [-1, 1]) Homogeneous depth: {}", caps->homogeneousDepth);
		_proto.info("(NDC bottom left) Origin bottom left: {}", caps->originBottomLeft);
		_proto.info("GPU count: {}", caps->numGPUs);
		_proto.info("GPU vendor ID: {}", caps->gpu->vendorId);
		_proto.info("GPU device ID: {}", caps->gpu->deviceId);

		_proto.info("Max draw calls: {}", caps->limits.maxDrawCalls);
		_proto.info("Max blits: {}", caps->limits.maxBlits);
		_proto.info("Max texture sizes: {}", caps->limits.maxTextureSize);
		_proto.info("Max texture layers: {}", caps->limits.maxTextureLayers);
		_proto.info("Max views: {}", caps->limits.maxViews);
		_proto.info("Max frame buffers: {}", caps->limits.maxFrameBuffers);
		_proto.info("Max frame buffer attachments: {}", caps->limits.maxFBAttachments);
		_proto.info("Max programs: {}", caps->limits.maxPrograms);
		_proto.info("Max shaders: {}", caps->limits.maxShaders);
		_proto.info("Max textures: {}", caps->limits.maxTextures);
		_proto.info("Max texture samplers: {}", caps->limits.maxTextureSamplers);
		_proto.info("Max compute bindings: {}", caps->limits.maxComputeBindings);
		_proto.info("Max vertex layouts: {}", caps->limits.maxVertexLayouts);
		_proto.info("Max vertex streams: {}", caps->limits.maxVertexStreams);
		_proto.info("Max index buffers: {}", caps->limits.maxIndexBuffers);
		_proto.info("Max vertex buffers: {}", caps->limits.maxVertexBuffers);
		_proto.info("Max dyn index buffers: {}", caps->limits.maxDynamicIndexBuffers);
		_proto.info("Max dyn vertex buffers: {}", caps->limits.maxDynamicVertexBuffers);
		_proto.info("Max uniforms: {}", caps->limits.maxUniforms);
		_proto.info("Max occlusion queries: {}", caps->limits.maxOcclusionQueries);
		_proto.info("Max encoder threads: {}", caps->limits.maxEncoders);
		_proto.info("Min resource command buffer size: {}", caps->limits.minResourceCbSize);
		_proto.info("Max transient vertex buffer size: {}", caps->limits.transientVbSize);
		_proto.info("Max transient index buffer size: {}", caps->limits.transientIbSize);
	}

	void get_runtime_stats(Diagnostics& _diag) noexcept {
		const auto& stats = *bgfx::getStats();
		_diag.graphics.used_vram = stats.gpuMemoryUsed;
		_diag.graphics.used_draw_calls = stats.numDraw;
		_diag.graphics.used_blit_calls = stats.numBlit;
		_diag.graphics.used_textures = stats.numTextures;
		_diag.graphics.used_shaders = stats.numShaders;
		_diag.graphics.used_programs = stats.numPrograms;
		_diag.graphics.used_uniforms = stats.numUniforms;
		_diag.graphics.used_vertex_buffers = stats.numVertexBuffers;
		_diag.graphics.used_index_buffers = stats.numIndexBuffers;
		_diag.graphics.used_dynamic_vertex_buffers = stats.numDynamicVertexBuffers;
		_diag.graphics.used_dynamic_index_buffers = stats.numDynamicIndexBuffers;
		_diag.graphics.used_frame_buffers = stats.numFrameBuffers;
	}

	void render_stats(const Runtime& _runtime) {
		const auto& chrono = _runtime.chrono();

		const auto viewport_pos_x = static_cast<std::uint16_t>(_runtime.render_data().scenery_viewport_position.x);
		const auto viewport_pos_y = static_cast<std::uint16_t>(_runtime.render_data().scenery_viewport_position.y);
		const auto viewport_width = static_cast<std::uint32_t>(_runtime.render_data().scenery_viewport_size.x);
		const auto viewport_height = static_cast<std::uint32_t>(_runtime.render_data().scenery_viewport_size.y);
		const auto screen_width = bgfx::getStats()->width;
		const auto screen_height = bgfx::getStats()->height;

		const auto pos_x = math::map_range<std::uint16_t>(viewport_pos_x, 0, screen_width, 0, 500);
		std::uint16_t pos_y = math::map_range<std::uint16_t>(viewport_pos_y, 0, screen_height, 0, 128) + 4;

		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(pos_x, pos_y, 0xF, "View x: %u y: %u w: %u h: %u", viewport_pos_x, viewport_pos_y, viewport_width
		                    , viewport_height);
		bgfx::dbgTextPrintf(pos_x, ++pos_y, 0xF, "Tick: %u, T: %.3f, FT: %.3f ms, FPS: %.2f", chrono.cycles, chrono.time
		                    , chrono.frame_time, chrono.fps);

	}
}
