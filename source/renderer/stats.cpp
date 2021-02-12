#include "stats.hpp"

#include "../../Include/PowerRonin/Runtime.hpp"
#include "../../extern/bgfx/bgfx/include/bgfx/bgfx.h"

namespace PowerRonin::Renderer
{
	void poll_limits(Diagnostics& _diag) noexcept
	{
		const auto& limits = bgfx::getCaps()->limits;
		_diag.Graphics.MaxVram = bgfx::getStats()->gpuMemoryMax;
		_diag.Graphics.MaxDrawCalls = limits.maxDrawCalls;
		_diag.Graphics.MaxBlitCalls = limits.maxComputeBindings;
		_diag.Graphics.MaxTextures = limits.maxTextures;
		_diag.Graphics.MaxShaders = limits.maxShaders;
		_diag.Graphics.MaxPrograms = limits.maxPrograms;
		_diag.Graphics.MaxUniforms = limits.maxUniforms;
		_diag.Graphics.MaxVertexBuffers = limits.maxVertexBuffers;
		_diag.Graphics.MaxIndexBuffers = limits.maxIndexBuffers;
		_diag.Graphics.MaxDynamicVertexBuffers = limits.maxDynamicVertexBuffers;
		_diag.Graphics.MaxDynamicIndexBuffers = limits.maxDynamicIndexBuffers;
		_diag.Graphics.MaxFrameBuffers = limits.maxFrameBuffers;
	}

	void dump_limits(AsyncProtocol& _proto)
	{
		const auto* const caps = bgfx::getCaps();
		_proto.Info("Supported flags: {:B}", caps->supported);
		_proto.Info("Vendor ID: {}", caps->vendorId);
		_proto.Info("Device ID: {}", caps->deviceId);
		_proto.Info("(NDC [-1, 1]) Homogeneous depth: {}", caps->homogeneousDepth);
		_proto.Info("(NDC bottom left) Origin bottom left: {}", caps->originBottomLeft);
		_proto.Info("GPU count: {}", caps->numGPUs);
		_proto.Info("GPU vendor ID: {}", caps->gpu->vendorId);
		_proto.Info("GPU device ID: {}", caps->gpu->deviceId);

		_proto.Info("Max draw calls: {}", caps->limits.maxDrawCalls);
		_proto.Info("Max blits: {}", caps->limits.maxBlits);
		_proto.Info("Max texture sizes: {}", caps->limits.maxTextureSize);
		_proto.Info("Max texture layers: {}", caps->limits.maxTextureLayers);
		_proto.Info("Max views: {}", caps->limits.maxViews);
		_proto.Info("Max frame buffers: {}", caps->limits.maxFrameBuffers);
		_proto.Info("Max frame buffer attachments: {}", caps->limits.maxFBAttachments);
		_proto.Info("Max programs: {}", caps->limits.maxPrograms);
		_proto.Info("Max shaders: {}", caps->limits.maxShaders);
		_proto.Info("Max textures: {}", caps->limits.maxTextures);
		_proto.Info("Max texture samplers: {}", caps->limits.maxTextureSamplers);
		_proto.Info("Max compute bindings: {}", caps->limits.maxComputeBindings);
		_proto.Info("Max vertex layouts: {}", caps->limits.maxVertexLayouts);
		_proto.Info("Max vertex streams: {}", caps->limits.maxVertexStreams);
		_proto.Info("Max index buffers: {}", caps->limits.maxIndexBuffers);
		_proto.Info("Max vertex buffers: {}", caps->limits.maxVertexBuffers);
		_proto.Info("Max dyn index buffers: {}", caps->limits.maxDynamicIndexBuffers);
		_proto.Info("Max dyn vertex buffers: {}", caps->limits.maxDynamicVertexBuffers);
		_proto.Info("Max uniforms: {}", caps->limits.maxUniforms);
		_proto.Info("Max occlusion queries: {}", caps->limits.maxOcclusionQueries);
		_proto.Info("Max encoder threads: {}", caps->limits.maxEncoders);
		_proto.Info("Min resource command buffer size: {}", caps->limits.minResourceCbSize);
		_proto.Info("Max transient vertex buffer size: {}", caps->limits.transientVbSize);
		_proto.Info("Max transient index buffer size: {}", caps->limits.transientIbSize);
	}

	void poll_stats(Diagnostics& _diag) noexcept
	{
		const auto* const stats = bgfx::getStats();
		_diag.Graphics.UsedVram = stats->gpuMemoryUsed;
		_diag.Graphics.UsedDrawCalls = stats->numDraw;
		_diag.Graphics.UsedBlitCalls = stats->numBlit;
		_diag.Graphics.UsedTextures = stats->numTextures;
		_diag.Graphics.UsedShaders = stats->numShaders;
		_diag.Graphics.UsedPrograms = stats->numPrograms;
		_diag.Graphics.UsedUniforms = stats->numUniforms;
		_diag.Graphics.UsedVertexBuffers = stats->numVertexBuffers;
		_diag.Graphics.UsedIndexBuffers = stats->numIndexBuffers;
		_diag.Graphics.UsedDynamicVertexBuffers = stats->numDynamicVertexBuffers;
		_diag.Graphics.UsedDynamicIndexBuffers = stats->numDynamicIndexBuffers;
		_diag.Graphics.UsedFrameBuffers = stats->numFrameBuffers;
	}

	void render_stats(const Runtime& _runtime)
	{
		//@formatter:off
		const auto& cfg = _runtime.Config();
		if (!cfg.Editor.ShowStats) [[unlikely]]
		{
			return;
		}
		const auto& chrono = _runtime.Chrono();
		const auto& diag = _runtime.Diagnostics();
		const auto* const stats = bgfx::getStats();
		const auto* const caps = bgfx::getCaps();
		const auto* const api_name = bgfx::getRendererName(bgfx::getRendererType());
		const auto& proj = _runtime.RenderData().ProjectionMatrix;
		auto view = _runtime.RenderData().ViewMatrix;
		constexpr auto byte_2_gb = 1024.f * 1024.f * 1024.f;
		const auto viewport_pos_x = static_cast<std::uint16_t>(_runtime.RenderData().PrimaryViewport.x);
		const auto viewport_pos_y = static_cast<std::uint16_t>(_runtime.RenderData().PrimaryViewport.y);
		const auto viewport_width = static_cast<std::uint32_t>(_runtime.RenderData().PrimaryViewport.z);
		const auto viewport_height = static_cast<std::uint32_t>(_runtime.RenderData().PrimaryViewport.w);
		const auto forward = normalize(Vector3<>(view[2]));
		const auto left = Vector3<>(-view[1][1], -view[2][1], -view[3][1]);
		view = Math::inverse(view);
		const auto pos = Vector3<>(view[3][0], view[3][1], view[3][2]);
		const auto fov = Math::degrees(std::atan(1.f / proj[1][1]) * 2.f);

		const std::uint16_t pos_x = viewport_pos_x / 8 + 4;
		std::uint16_t pos_y = viewport_pos_y / (cfg.Editor.ShowBigStats ? 16 : 8) + 2;

		bgfx::dbgTextClear(0, !cfg.Editor.ShowBigStats);
		bgfx::dbgTextPrintf(pos_x, pos_y, cfg.Editor.StatsTextColor, "%s, DrawCalls: %u, SceneryDrawCalls: %u, ComputeCalls: %u, BlitCalls: %u", api_name, stats->numDraw,
		                    diag.Graphics.SceneryMeshDrawCalls, stats->numCompute, stats->numBlit);
		bgfx::dbgTextPrintf(pos_x, ++pos_y, cfg.Editor.StatsTextColor, "View x: %u y: %u w: %u h: %u", viewport_pos_x, viewport_pos_y, viewport_width, viewport_height);
		bgfx::dbgTextPrintf(pos_x, ++pos_y, cfg.Editor.StatsTextColor, "Tick: %u, Time: %.2f", chrono.Cycles, chrono.Time);
		bgfx::dbgTextPrintf(pos_x, ++pos_y, cfg.Editor.StatsTextColor, "FPS: %.2f, DeltaTime: %f, FrameTime: %.3fms", chrono.Fps, chrono.FrameTime, chrono.DeltaTime);
		bgfx::dbgTextPrintf(pos_x, ++pos_y, cfg.Editor.StatsTextColor, "Position: %.2f %.2f %.2f, Forward: %.2f %.2f %.2f, Left: %.2f %.2f %.2f, FOV: %.1f", pos.x, pos.y, pos.z, forward.x,
		                    forward.y, forward.z, left.x, left.y, left.z, fov);
		bgfx::dbgTextPrintf(pos_x, ++pos_y, cfg.Editor.StatsTextColor, "VRAM %.2fGB/%.2fGB, TexMEM: %.2fGB", stats->gpuMemoryUsed / byte_2_gb, stats->gpuMemoryMax / byte_2_gb,
		                    stats->textureMemoryUsed / byte_2_gb);

		const auto& view_matrix = _runtime.RenderData().ViewMatrix;
		const auto& projection_matrix = _runtime.RenderData().ViewMatrix;
		const auto& view_projection_matrix = _runtime.RenderData().ViewProjectionMatrix;

		if (!cfg.Editor.ShowMatrixStats) [[unlikely]]
		{
			return;
		}

		auto print_matrix = [pos_x, &pos_y, color = cfg.Editor.StatsTextColor](const auto& _mtx, const auto* const _name) noexcept
		{
			bgfx::dbgTextPrintf(pos_x, ++pos_y, color, _name);
			bgfx::dbgTextPrintf(pos_x, ++pos_y, color, "[%.3f %.3f %.3f %.3f]", _mtx[0][0], _mtx[0][1], _mtx[0][2], _mtx[0][3]);
			bgfx::dbgTextPrintf(pos_x, ++pos_y, color, "[%.3f %.3f %.3f %.3f]", _mtx[1][0], _mtx[1][1], _mtx[1][2], _mtx[1][3]);
			bgfx::dbgTextPrintf(pos_x, ++pos_y, color, "[%.3f %.3f %.3f %.3f]", _mtx[2][0], _mtx[2][1], _mtx[2][2], _mtx[2][3]);
			bgfx::dbgTextPrintf(pos_x, ++pos_y, color, "[%.3f %.3f %.3f %.3f]", _mtx[3][0], _mtx[3][1], _mtx[3][2], _mtx[3][3]);
		};

		print_matrix(view_matrix, "View Matrix (4x4)");
		print_matrix(projection_matrix, "Projection Matrix (4x4)");
		print_matrix(view_projection_matrix, "View Projection Matrix (4x4)");

		//@formatter:on
	}
}
