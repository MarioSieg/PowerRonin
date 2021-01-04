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

#pragma once

#include <cstdint>

#include "../../include/power_ronin/mathlib.hpp"
#include "../../include/power_ronin/mesh.hpp"
#include "../../include/power_ronin/texture.hpp"
#include "../../include/power_ronin/mesh_renderer.hpp"

#include "gl_headers.hpp"
#include "uniform.hpp"

namespace power_ronin
{
	class Transform;
	class MeshRenderer;
	class Diagnostics;
	class Config;
	class AsyncProtocol;
}

namespace power_ronin::renderer
{
	/// <summary>
	/// Represents a high level GPU which can draw stuff.
	/// </summary>
	class GPU final
	{
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
		auto initialize_drivers(const Config& _config, AsyncProtocol& _proto) const -> bool;

		/// <summary>
		/// Shutdown rendering backend.
		/// </summary>
		void shutdown_drivers() const;

		/// <summary>
		/// Begin and clear frame.
		/// </summary>
		/// <returns></returns>
		void clear_view(const bgfx::ViewId _view = 0
		                , const std::uint16_t _flags = BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		                , const float _depth = 1.F
		                , const std::uint32_t _rgba = 0xFFFFFFFF) const noexcept;


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
		void end_frame() noexcept;

		/// <summary>
		/// Set camera matrices.
		/// </summary>
		/// <param name="_view"></param>
		/// <param name="_proj"></param>
		/// <param name="_view_id"></param>
		/// <returns></returns>
		void set_camera(const bgfx::ViewId _view_id, const SimdMatrix4x4<>& _view, const SimdMatrix4x4<>& _proj) const noexcept;

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
		void set_texture(const Texture& _texture, const Uniform& _sampler, const std::uint8_t _stage) const noexcept;

		static constexpr auto DEFAULT_STATE_FLAGS = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_MSAA | BGFX_STATE_CULL_CCW;

		/// <summary>
		/// Draw mesh
		/// </summary>
		/// <param name="_shader"></param>
		/// <param name="_state_flags"></param>
		/// <param name="_view_id"></param>
		/// <param name="_depth"></param>
		/// <returns></returns>
		void draw(bgfx::ProgramHandle _shader
		          , bgfx::ViewId _view_id
		          , const std::uint64_t _state_flags = DEFAULT_STATE_FLAGS
		          , std::uint8_t _depth = 0) const noexcept;

		/// <summary>
		/// Set the set_viewport.
		/// </summary>
		/// <param name="_xy"></param>
		/// <param name="_wh"></param>
		/// <param name="_view_id"></param>
		/// <returns></returns>
		void set_viewport(const SimdVector2<> _xy, const SimdVector2<> _wh, const bgfx::ViewId _view_id) const noexcept;
	};
}
