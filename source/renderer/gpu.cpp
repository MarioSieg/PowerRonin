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

#include "gpu.hpp"
#include "stats.hpp"
#include "../../extern/bullet3/examples/ThirdPartyLibs/imgui/imgui.h"

#include "../../include/power_ronin/proto.hpp"
#include "../../include/power_ronin/env.hpp"
#include "../../include/power_ronin/config.hpp"
#include "../../include/power_ronin/transform.hpp"
#include "../../include/power_ronin/mesh_renderer.hpp"
#include "../platform/platform.hpp"

namespace PowerRonin::Renderer
{
	void GPU::initialize_drivers(const SystemConfig& _config, AsyncProtocol& _proto) const
	{
		if (Platform::NativeWindowHandle == nullptr) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Native window handle was nullptr!");
		}

		bgfx::Init init{};
		init.type = bgfx::RendererType::Direct3D11;
		init.debug = DebugMode;
		init.platformData.nwh = Platform::NativeWindowHandle;
		init.profile = DebugMode;

		switch (_config.Graphics.MsaaMode)
		{
			case MsaaMode::X2: init.resolution.reset |= BGFX_RESET_MSAA_X2;
				break;
			case MsaaMode::X4: init.resolution.reset |= BGFX_RESET_MSAA_X4;
				break;
			case MsaaMode::X8: init.resolution.reset |= BGFX_RESET_MSAA_X8;
				break;
			case MsaaMode::X16: init.resolution.reset |= BGFX_RESET_MSAA_X16;
				break;
		}

		if (_config.Graphics.EnableHighDpiMode) [[likely]]
		{
			init.resolution.reset |= BGFX_RESET_HIDPI;
		}

		if (_config.Graphics.EnableSrgbMode) [[likely]]
		{
			init.resolution.reset |= BGFX_RESET_SRGB_BACKBUFFER;
		}

		if (_config.Graphics.EnableHdr10) [[likely]]
		{
			init.resolution.reset |= BGFX_RESET_HDR10;
		}

		if (_config.Graphics.EnableMaxAnisotropy) [[likely]]
		{
			init.resolution.reset |= BGFX_RESET_MAXANISOTROPY;
		}

		if (_config.Display.VSync) [[likely]]
		{
			//init.resolution.reset |= BGFX_RESET_VSYNC;
		}

		init.resolution.width = _config.Display.Resolution.Width;
		init.resolution.height = _config.Display.Resolution.Height;

		if (!bgfx::init(init)) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to initialize backend renderer!");
		}

		bgfx::setDebug(BGFX_DEBUG_TEXT);

		_proto.Separator();
		_proto.Critical("Initializing GPU engine backend...");

		std::array<bgfx::RendererType::Enum, bgfx::RendererType::Count> supported = {};
		getSupportedRenderers(static_cast<std::uint8_t>(supported.size()), supported.data());

		for (const auto renderer : supported)
		{
			if (renderer != bgfx::RendererType::Noop)
			{
				_proto.Info("Found supported backend API: {}", getRendererName(renderer));
			}
		}

		_proto.Info("Using GPU backend API: {}", getRendererName(init.type));

		dump_limits(_proto);
	}

	void GPU::shutdown_drivers() const
	{
		// TODO
		//bgfx::shutdown();
	}

	void GPU::clear_view(const bgfx::ViewId _view
	                     , const std::uint16_t _flags
	                     , const float _depth
	                     , const std::uint32_t _rgba) const noexcept
	{
		bgfx::setViewClear(_view, _flags, _rgba, _depth, 0);
	}

	void GPU::sort_draw_calls(const bgfx::ViewId _view) const noexcept
	{
		bgfx::touch(_view);
	}

	void GPU::end_frame() noexcept
	{
		bgfx::frame();
	}

	void GPU::set_camera(const bgfx::ViewId _view_id, const Matrix4x4<>& _view,
	                     const Matrix4x4<>& _proj) const noexcept
	{
		bgfx::setViewTransform(_view_id, value_ptr(_view), value_ptr(_proj));
	}

	void GPU::set_transform(const Transform& _transform) const noexcept
	{
		bgfx::setTransform(value_ptr(_transform.matrix()));
	}

	void GPU::set_transform(const float (&_matrix)[16]) const noexcept
	{
		bgfx::setTransform(&*_matrix);
	}

	void GPU::set_transform(const float* const _matrix) const noexcept
	{
		bgfx::setTransform(_matrix);
	}

	void GPU::set_mesh_buffer(const Mesh& _mesh) const noexcept
	{
		assert(_mesh.is_uploaded());

		const auto vb_buffer = bgfx::VertexBufferHandle{_mesh.VertexBufferId()};
		const auto ib_buffer = bgfx::IndexBufferHandle{_mesh.IndexBufferId()};

		assert(bgfx::isValid(vb_buffer));
		assert(bgfx::isValid(ib_buffer));

		setIndexBuffer(ib_buffer);
		setVertexBuffer(0, vb_buffer);
	}

	void GPU::set_texture(const Texture& _texture, const Uniform& _sampler, const std::uint8_t _stage) const noexcept
	{
		assert(_texture.is_uploaded());

		const auto view = bgfx::TextureHandle{_texture.texel_buffer_id()};

		assert(bgfx::isValid(view));
		assert(bgfx::isValid(_sampler.handle()));

		setTexture(_stage, _sampler.handle(), view);
	}

	void GPU::draw(const bgfx::ProgramHandle _shader
	               , const bgfx::ViewId _view_id
	               , const std::uint64_t _state_flags
	               , const std::uint8_t _depth) const noexcept
	{
		assert(bgfx::isValid(_shader));
		bgfx::setState(_state_flags);
		submit(_view_id, _shader, _depth);
	}

	void GPU::set_viewport(const Vector4<> _xywh, const bgfx::ViewId _view_id) const noexcept
	{
		bgfx::setViewRect(_view_id, _xywh.x, _xywh.y, _xywh.z, _xywh.w);
	}
}
