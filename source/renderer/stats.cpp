#include "stats.hpp"

#include "../../include/dce/runtime.hpp"
#include "../../extern/bgfx/bgfx/include/bgfx/bgfx.h"

namespace dce::renderer {
	void poll_limits(Diagnostics& _diag) noexcept {
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

	void poll_stats(Diagnostics& _diag) noexcept {
		const auto* const stats = bgfx::getStats();
		_diag.graphics.used_vram = stats->gpuMemoryUsed;
		_diag.graphics.used_draw_calls = stats->numDraw;
		_diag.graphics.used_blit_calls = stats->numBlit;
		_diag.graphics.used_textures = stats->numTextures;
		_diag.graphics.used_shaders = stats->numShaders;
		_diag.graphics.used_programs = stats->numPrograms;
		_diag.graphics.used_uniforms = stats->numUniforms;
		_diag.graphics.used_vertex_buffers = stats->numVertexBuffers;
		_diag.graphics.used_index_buffers = stats->numIndexBuffers;
		_diag.graphics.used_dynamic_vertex_buffers = stats->numDynamicVertexBuffers;
		_diag.graphics.used_dynamic_index_buffers = stats->numDynamicIndexBuffers;
		_diag.graphics.used_frame_buffers = stats->numFrameBuffers;
	}

	void render_stats(const Runtime& _runtime) {
		//@formatter:off
		const auto& chrono = _runtime.chrono();
		const auto& diag = _runtime.diagnostics();
		const auto* const stats = bgfx::getStats();
		const auto* const caps = bgfx::getCaps();
		auto view = _runtime.render_data().view_matrix;
		const auto& proj = _runtime.render_data().projection_matrix;
		constexpr auto byte_2_gb = 1024.f * 1024.f * 1024.f;
		const auto viewport_pos_x = static_cast<std::uint16_t>(_runtime.render_data().scenery_viewport_position.x);
		const auto viewport_pos_y = static_cast<std::uint16_t>(_runtime.render_data().scenery_viewport_position.y);
		const auto viewport_width = static_cast<std::uint32_t>(_runtime.render_data().scenery_viewport_size.x);
		const auto viewport_height = static_cast<std::uint32_t>(_runtime.render_data().scenery_viewport_size.y);
		const auto forward = normalize(SimdVector3<>(view[2]));
		const auto left = SimdVector3<>(-view[1][1], -view[2][1], -view[3][1]);
		view = math::inverse(view);
		const auto pos = SimdVector3<>(view[3][0], view[3][1], view[3][2]);
		const auto fov = math::degrees(atan(1.f / proj[1][1]) * 2.f);
		const std::uint16_t pos_x = viewport_pos_x / 8 + 4;
		std::uint16_t pos_y = viewport_pos_y / 16 + 2;
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(pos_x, pos_y, 0x8F, "%s, DrawCalls: %u, SceneryDrawCalls: %u, ComputeCalls: %u, BlitCalls: %u", bgfx::getRendererName(bgfx::getRendererType()), stats->numDraw,
		                    diag.graphics.scenery_mesh_drawcalls, stats->numCompute, stats->numBlit);
		bgfx::dbgTextPrintf(pos_x, ++pos_y, 0x8F, "View x: %u y: %u w: %u h: %u", viewport_pos_x, viewport_pos_y, viewport_width, viewport_height);
		bgfx::dbgTextPrintf(pos_x, ++pos_y, 0x8F, "Tick: %u, Time: %.2f", chrono.cycles, chrono.time);
		bgfx::dbgTextPrintf(pos_x, ++pos_y, 0x8F, "FPS: %.2f, DeltaTime: %f, FrameTime: %.3fms", chrono.fps, chrono.frame_time, chrono.delta_time);
		bgfx::dbgTextPrintf(pos_x, ++pos_y, 0x8F, "Position: %.2f %.2f %.2f, Forward: %.2f %.2f %.2f, Left: %.2f %.2f %.2f, FOV: %.1f", pos.x, pos.y, pos.z, forward.x, forward.y, forward.z, left.x,
		                    left.y, left.z, fov);
		bgfx::dbgTextPrintf(pos_x, ++pos_y, 0x8F, "VRAM %.2fGB/%.2fGB, TexMEM: %.2fGB", stats->gpuMemoryUsed / byte_2_gb, stats->gpuMemoryMax / byte_2_gb, stats->textureMemoryUsed / byte_2_gb);
		//@formatter:on
	}
}
