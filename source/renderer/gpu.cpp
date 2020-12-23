#include "gpu.hpp"
#include "stats.hpp"

#include "../../include/dce/proto.hpp"
#include "../../include/dce/env.hpp"
#include "../../include/dce/config.hpp"
#include "../../include/dce/transform.hpp"
#include "../../include/dce/mesh_renderer.hpp"
#include "../platform/platform.hpp"

namespace dce::renderer {
	auto GPU::initialize_drivers(const Config& _config, AsyncProtocol& _proto) const -> bool {
		if (platform::NATIVE_WINDOW_HANDLE == nullptr) {
			_proto.error(
				"platform::NATIVE_WINDOW_HANDLE was nullptr! Platform system must be initialized before render system!");
			return false;
		}

		bgfx::Init init{};
		init.type = bgfx::RendererType::Direct3D11;
		init.debug = DEBUG_MODE;
		init.platformData.nwh = platform::NATIVE_WINDOW_HANDLE;
		init.profile = DEBUG_MODE;

		switch (_config.graphics.msaa_mode) {
		case MsaaMode::X2: init.resolution.reset |= BGFX_RESET_MSAA_X2;
			break;
		case MsaaMode::X4: init.resolution.reset |= BGFX_RESET_MSAA_X4;
			break;
		case MsaaMode::X8: init.resolution.reset |= BGFX_RESET_MSAA_X8;
			break;
		case MsaaMode::X16: init.resolution.reset |= BGFX_RESET_MSAA_X16;
			break;
		default: case MsaaMode::OFF: ;
		}

		[[unlikely]] if (_config.graphics.enable_high_dpi_mode) {
			init.resolution.reset |= BGFX_RESET_HIDPI;
		}

		[[likely]] if (_config.graphics.enable_srgb_backbuffer) {
			init.resolution.reset |= BGFX_RESET_SRGB_BACKBUFFER;
		}

		[[likely]] if (_config.graphics.enable_hdr10) {
			init.resolution.reset |= BGFX_RESET_HDR10;
		}

		[[likely]] if (_config.graphics.enable_max_anisotropy) {
			init.resolution.reset |= BGFX_RESET_MAXANISOTROPY;
		}

		[[likely]] if (_config.display.vsync) {
			init.resolution.reset |= BGFX_RESET_VSYNC;
		}

		init.resolution.width = _config.display.width;
		init.resolution.height = _config.display.height;

		if (!bgfx::init(init)) {
			_proto.error("Failed to initialize GPU engine backend!");
			return false;
		}

		bgfx::setDebug(BGFX_DEBUG_TEXT);

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
		// TODO
		//bgfx::shutdown();
	}

	void GPU::clear_view(const bgfx::ViewId _view
	                     , const std::uint16_t _flags
	                     , const float _depth
	                     , const std::uint32_t _rgba) const noexcept {
		bgfx::setViewClear(_view, _flags, _rgba, _depth, 0);
	}

	void GPU::sort_draw_calls(const bgfx::ViewId _view) const noexcept {
		bgfx::touch(_view);
	}

	void GPU::end_frame() const noexcept {
		bgfx::frame();
	}

	void GPU::set_camera(const bgfx::ViewId _view_id, const SimdMatrix4x4<>& _view,
	                     const SimdMatrix4x4<>& _proj) const noexcept {
		bgfx::setViewTransform(_view_id, value_ptr(_view), value_ptr(_proj));
	}

	void GPU::set_transform(const Transform& _transform) const noexcept {
		bgfx::setTransform(value_ptr(_transform.calculate_matrix()));
	}

	void GPU::set_transform(const float (&_matrix)[16]) const noexcept {
		bgfx::setTransform(&*_matrix);
	}

	void GPU::set_transform(const float* const _matrix) const noexcept {
		bgfx::setTransform(_matrix);
	}

	void GPU::set_mesh_buffer(const Mesh& _mesh) const noexcept {
		assert(_mesh.is_uploaded());

		const auto vb_buffer = bgfx::VertexBufferHandle{_mesh.get_vertex_buffer_id()};
		const auto ib_buffer = bgfx::IndexBufferHandle{_mesh.get_index_buffer_id()};

		assert(bgfx::isValid(vb_buffer));
		assert(bgfx::isValid(ib_buffer));

		setIndexBuffer(ib_buffer);
		setVertexBuffer(0, vb_buffer);
	}

	void GPU::set_texture(const Texture& _texture, const bgfx::UniformHandle _sampler,
	                      const std::uint8_t _stage) const noexcept {
		assert(_texture.is_uploaded());

		const auto view = bgfx::TextureHandle{_texture.get_texel_buffer_id()};

		assert(bgfx::isValid(view));

		setTexture(_stage, _sampler, view);
	}

	void GPU::draw(const bgfx::ProgramHandle _shader
	               , const bgfx::ViewId _view_id
	               , const std::uint64_t _state_flags
	               , const std::uint8_t _depth) const noexcept {
		assert(bgfx::isValid(_shader));
		bgfx::setState(_state_flags);
		submit(_view_id, _shader, _depth);
	}

	void GPU::set_viewport(const SimdVector2<> _xy, const SimdVector2<> _wh, const bgfx::ViewId _view_id) const noexcept {
		bgfx::setViewRect(_view_id, _xy.x, _xy.y, _wh.x, _wh.y);
	}

	void GPU::set_uniform(const bgfx::UniformHandle _handle, const SimdVector4<>& _value) const noexcept {
		setUniform(_handle, value_ptr(_value));
	}

	void GPU::set_uniform(const bgfx::UniformHandle _handle, const SimdMatrix3x3<>& _value) const noexcept {
		setUniform(_handle, value_ptr(_value));
	}

	void GPU::set_uniform(const bgfx::UniformHandle _handle, const SimdMatrix4x4<>& _value) const noexcept {
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
