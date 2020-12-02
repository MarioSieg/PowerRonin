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

#include <cstdint>

#include "../../include/dce/mathlib.hpp"
#include "../../include/dce/mesh.hpp"
#include "../../include/dce/texture.hpp"
#include "../../include/dce/mesh_renderer.hpp"

#include "gl_headers.hpp"

namespace dce {
	class Transform;
	class MeshRenderer;
	class Diagnostics;
	class Config;
	class AsyncProtocol;
}

namespace dce::renderer {
	/// <summary>
	/// Represents a high level GPU which can draw stuff.
	/// </summary>
	class GPU final {
	public:
		GPU() noexcept = default;
		GPU(const GPU&) = delete;
		GPU(GPU&&) = delete;
		auto operator=(const GPU&) -> GPU& = delete;
		auto operator=(GPU&&) -> GPU& = delete;
		~GPU() = default;

		/// <summary>
		/// Initialize rendering backend.
		/// </summary>
		/// <param name="_config"></param>
		/// <param name="_proto"></param>
		/// <returns></returns>
		auto initialize_drivers(const Config& _config, AsyncProtocol& _proto) -> bool;

		/// <summary>
		/// Shutdown rendering backend.
		/// </summary>
		void shutdown_drivers() const;

		/// <summary>
		/// Begin and clear frame.
		/// </summary>
		/// <returns></returns>
		void clear_view(const bgfx::ViewId _view = 0, const std::uint16_t _flags = BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, const float _depth = 1.F) const noexcept;


		/// <summary>
		/// Sort the draw calls on this view.
		/// </summary>
		/// <param name="_view"></param>
		/// <returns></returns>
		void sort_draw_calls(const bgfx::ViewId _view = 0) const noexcept;

		/// <summary>
		/// End frame and kick render thread.
		/// </summary>
		/// <returns></returns>
		void end_frame() const noexcept;

		/// <summary>
		/// Set camera matrices.
		/// </summary>
		/// <param name="_view"></param>
		/// <param name="_proj"></param>
		/// <param name="_view_id"></param>
		/// <returns></returns>
		void set_camera(const bgfx::ViewId _view_id, const Matrix4x4<>& _view, const Matrix4x4<>& _proj) const noexcept;

		/// <summary>
		/// Set mesh world transform matrix.
		/// </summary>
		/// <param name="_transform"></param>
		/// <returns></returns>
		void set_transform(const Transform& _transform) const noexcept;

		/// <summary>
		/// Set mesh world transform matrix.
		/// </summary>
		/// <param name="_matrix"></param>
		/// <returns></returns>
		void set_transform(const float (&_matrix)[16]) const noexcept;

		/// <summary>
		/// Set mesh world transform matrix.
		/// </summary>
		/// <param name="_matrix"></param>
		/// <returns></returns>
		void set_transform(const float* const _matrix) const noexcept;

		/// <summary>
		/// Set mesh buffers.
		/// </summary>
		/// <param name="_mesh"></param>
		/// <returns></returns>
		void set_mesh_buffer(const Mesh& _mesh) const noexcept;

		/// <summary>
		/// Set texture.
		/// </summary>
		/// <param name="_texture"></param>
		/// <param name="_sampler"></param>
		/// <returns></returns>
		void set_texture(const Texture& _texture, bgfx::UniformHandle _sampler) const noexcept;

		/// <summary>
		/// Draw mesh
		/// </summary>
		/// <param name="_shader"></param>
		/// <param name="_state_flags"></param>
		/// <param name="_view_id"></param>
		/// <param name="_depth"></param>
		/// <returns></returns>
		void draw(bgfx::ProgramHandle _shader, bgfx::ViewId _view_id = 0, const std::uint64_t _state_flags = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_MSAA | BGFX_STATE_CULL_CCW, std::uint8_t _depth = 0) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_handle"></param>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set_uniform(bgfx::UniformHandle _handle, const Vector4<>& _value) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_handle"></param>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set_uniform(bgfx::UniformHandle _handle, const Matrix3x3<>& _value) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_handle"></param>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set_uniform(bgfx::UniformHandle _handle, const Matrix4x4<>& _value) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_handle"></param>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set_uniform(bgfx::UniformHandle _handle, const float (&_value)[4]) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_handle"></param>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set_uniform(bgfx::UniformHandle _handle, const float (&_value)[9]) const noexcept;

		/// <summary>
		/// Set uniform.
		/// </summary>
		/// <param name="_handle"></param>
		/// <param name="_value"></param>
		/// <returns></returns>
		void set_uniform(bgfx::UniformHandle _handle, const float (&_value)[16]) const noexcept;


	private:
		std::uint16_t width_ = 0;
		std::uint16_t height_ = 0;
	};
}
