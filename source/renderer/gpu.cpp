// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: gpu.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 14.11.2020 13:44

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

	void GPU::shutdown_drivers() const {
		bgfx::shutdown();
	}

	void GPU::begin_frame() const noexcept {
		bgfx::setViewClear(0, BGFX_CLEAR_DEPTH | BGFX_CLEAR_COLOR, 0, 1.F, 0);
		bgfx::setViewRect(0, 0, 0, this->width_, this->height_);
	}

	void GPU::sort_drawcalls(const std::uint8_t _view_id) const noexcept {
		bgfx::touch(_view_id);
	}

	void GPU::end_frame() const noexcept {
		bgfx::frame();
	}

	void GPU::set_camera(const Matrix4x4 &_view, const Matrix4x4 &_proj, const std::uint8_t _view_id) const noexcept {
		bgfx::setViewTransform(_view_id, value_ptr(_view), value_ptr(_proj));
	}

	void GPU::render_mesh(const Transform &_transform, const MeshRenderer &_renderer) const {
		this->set_states();
		this->set_transform(_transform);
		this->set_mesh(_renderer.mesh);
		this->set_texture(_renderer.shader->get_sampler_id(), _renderer.texture);
		this->submit(_renderer.shader);
	}

	void GPU::set_transform(const Transform &_transform) const noexcept {
		bgfx::setTransform(value_ptr(_transform.calculate_matrix()));
	}

	void GPU::set_mesh(const ResourceHandle<Mesh> &_mesh) const noexcept {
		const auto vb_id = bgfx::VertexBufferHandle{_mesh->get_vertex_buffer_id()};
		const auto ib_id = bgfx::IndexBufferHandle{_mesh->get_index_buffer_id()};
		assert(_mesh->is_uploaded());
		assert(bgfx::isValid(vb_id));
		assert(bgfx::isValid(ib_id));
		setVertexBuffer(0, vb_id);
		setIndexBuffer(ib_id);
	}

	void GPU::set_texture(const std::uint16_t _sampler, const ResourceHandle<Texture> &_texture) const noexcept {
		assert(_texture->is_uploaded());
		const auto texture_handle = bgfx::TextureHandle{_texture->get_texel_buffer_id()};
		assert(bgfx::isValid(texture_handle));
		const auto sampler_handle = bgfx::UniformHandle{_sampler};
		assert(bgfx::isValid(sampler_handle));
		setTexture(0, sampler_handle, texture_handle);
	}

	void GPU::submit(const ResourceHandle<Shader> &_shader, const std::uint8_t _view_id) const noexcept {
		assert(_shader->is_uploaded());
		const auto program_handle = bgfx::ProgramHandle{_shader->get_program_id()};
		assert(bgfx::isValid(program_handle));
		bgfx::submit(_view_id, program_handle);
	}

	void GPU::set_states() const noexcept {
		bgfx::setState(
			BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_MSAA |
			BGFX_STATE_CULL_CCW);
	}
}
