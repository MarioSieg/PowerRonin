// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: gpu.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "gpu.hpp"
#include "stats.hpp"

#include "../../include/dce/proto.hpp"
#include "../../include/dce/env.hpp"
#include "../../include/dce/config.hpp"
#include "../../include/dce/transform.hpp"
#include "../../include/dce/mesh_renderer.hpp"

#include "../platform/platform.hpp"

#include "../../extern/bgfx/bgfx/include/bgfx/bgfx.h"

namespace dce::renderer {

	auto GPU::initialize_drivers(const Config &_config, AsyncProtocol &_proto) -> bool {
		if (platform::NATIVE_WINDOW_HANDLE == nullptr) {
			_proto.error(
				"platform::NATIVE_WINDOW_HANDLE was nullptr! Platform system must be initialized before render system!");
			return false;
		}

		bgfx::Init init{};
		init.limits.maxEncoders = 16;
		init.type = bgfx::RendererType::Direct3D11;
		init.debug = DEBUG_MODE;
		init.platformData.nwh = platform::NATIVE_WINDOW_HANDLE;
		init.profile = DEBUG_MODE;
		init.resolution.reset = BGFX_RESET_MSAA_X16;
		init.resolution.width = _config.display.width;
		init.resolution.height = _config.display.height;

		if (!bgfx::init(init)) {
			_proto.error("Failed to initialize GPU engine backend!");
			return false;
		}

		this->width_ = _config.display.width;
		this->height_ = _config.display.height;

		_proto.separator();
		_proto.critical("Initializing GPU engine backend...");

		std::array<bgfx::RendererType::Enum, bgfx::RendererType::Count> supported = {};
		getSupportedRenderers(static_cast<std::uint8_t>(supported.size()), supported.data());

		for (const auto renderer : supported) {
			if (renderer != bgfx::RendererType::Noop) {
				_proto.info("Found supported backend API: {}", getRendererName(renderer));
			}
		}

		_proto.info("Using GPU backend API: {}", getRendererName(init.type));

		dump_limits(_proto);

		return true;
	}

	void GPU::shutdown_drivers() {
		bgfx::shutdown();
	}

	void GPU::begin_frame() const noexcept {
		bgfx::setViewClear(0, BGFX_CLEAR_DEPTH | BGFX_CLEAR_COLOR, 0xFFFFFFFF, 1.F, 0);
		bgfx::setViewRect(0, 0, 0, this->width_, this->height_);
	}

	void GPU::sort_drawcalls(const bgfx::ViewId _view_id) const noexcept {
		bgfx::touch(_view_id);
	}

	void GPU::end_frame() const noexcept {
		bgfx::frame();
	}

	void GPU::set_camera(const Matrix4x4<> &_view, const Matrix4x4<> &_proj, const bgfx::ViewId _view_id) const noexcept {
		bgfx::setViewTransform(_view_id, value_ptr(_view), value_ptr(_proj));
	}

	void GPU::set_transform(const Transform &_transform) const noexcept {
		bgfx::setTransform(value_ptr(_transform.calculate_matrix()));
	}

	void GPU::set_mesh_buffer(const Mesh &_mesh) const noexcept {
		assert(_mesh.is_uploaded());

		const auto vb_buffer = bgfx::VertexBufferHandle{_mesh.get_vertex_buffer_id()};
		const auto ib_buffer = bgfx::IndexBufferHandle{_mesh.get_index_buffer_id()};

		assert(bgfx::isValid(vb_buffer));
		assert(bgfx::isValid(ib_buffer));

		setIndexBuffer(ib_buffer);
		setVertexBuffer(0, vb_buffer);
	}

	void GPU::set_texture(const Texture &_texture, const bgfx::UniformHandle _sampler) const noexcept {
		assert(_texture.is_uploaded());

		const auto view = bgfx::TextureHandle{_texture.get_texel_buffer_id()};

		assert(bgfx::isValid(view));

		setTexture(0, _sampler, view);
	}

	void GPU::draw(const bgfx::ProgramHandle _shader, const bgfx::ViewId _view_id, const std::uint8_t _depth) const noexcept {
		assert(bgfx::isValid(_shader));

		constexpr auto states = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LESS |
			BGFX_STATE_MSAA | BGFX_STATE_CULL_CCW;

		bgfx::setState(states);
		submit(_view_id, _shader, _depth);
	}

	void GPU::set_uniform(const bgfx::UniformHandle _handle, const Vector4<> &_value) const noexcept {
		setUniform(_handle, value_ptr(_value));
	}

	void GPU::set_uniform(const bgfx::UniformHandle _handle, const Matrix3x3<> &_value) const noexcept {
		setUniform(_handle, value_ptr(_value));
	}

	void GPU::set_uniform(const bgfx::UniformHandle _handle, const Matrix4x4<> &_value) const noexcept {
		setUniform(_handle, value_ptr(_value));
	}

	void GPU::set_uniform(const bgfx::UniformHandle _handle, const float (&_value)[4]) const noexcept {
		setUniform(_handle, &*_value);
	}

	void GPU::set_uniform(const bgfx::UniformHandle _handle, const float (&_value)[9]) const noexcept {
		setUniform(_handle, &*_value);
	}

	void GPU::set_uniform(const bgfx::UniformHandle _handle, const float (&_value)[16]) const noexcept {
		setUniform(_handle, &*_value);
	}
}
