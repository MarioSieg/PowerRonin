// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: gpu.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include <cstdint>

#include "../../include/dce/mathlib.hpp"
#include "../../include/dce/mesh.hpp"
#include "../../include/dce/texture.hpp"
#include "gl_headers.hpp"

namespace dce {
	class Transform;
	class MeshRenderer;
	class Diagnostics;
	class Config;
	class AsyncProtocol;
}

namespace dce::renderer {
	/* Represents a high level GPU which can draw stuff. */
	class GPU final {
	public:
		GPU() noexcept = default;
		GPU(const GPU &) = delete;
		GPU(GPU &&) = delete;
		auto operator=(const GPU &) -> GPU& = delete;
		auto operator=(GPU &&) -> GPU& = delete;
		~GPU() = default;

		/* Initialize rendering backend. */
		auto initialize_drivers(const Config &_config, AsyncProtocol &_proto) -> bool;

		/* Shutdown rendering backend. */
		void shutdown_drivers();

		/* Begin and clear frame. */
		void begin_frame() const noexcept;

		/* Sort draws. (Call after gui before ordinary drawcalls) */
		void sort_drawcalls(const bgfx::ViewId _view_id = 0) const noexcept;

		/* End frame and kick render thread. */
		void end_frame() const noexcept;

		/* Set camera matrices. */
		void set_camera(const Matrix4x4<> &_view, const Matrix4x4<> &_proj, const bgfx::ViewId _view_id = 0) const noexcept;

		/* Set mesh world transform matrix. */
		void set_transform(const Transform &_transform) const noexcept;

		/* Set mesh buffers. */
		void set_mesh_buffer(const Mesh &_mesh) const noexcept;

		/* Set texture. */
		void set_texture(const Texture &_texture, const bgfx::UniformHandle _sampler) const noexcept;

		/* Draw mesh */
		void draw(const bgfx::ProgramHandle _shader, const bgfx::ViewId _view_id = 0
		          , const std::uint8_t _depth = 0) const noexcept;

	private:
		std::uint16_t width_ = 0;
		std::uint16_t height_ = 0;
	};
}
