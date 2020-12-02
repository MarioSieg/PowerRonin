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

#include "../ishader.hpp"

namespace dce::renderer::shaders {
	class Lambert final : public IShader {
	public:
		explicit Lambert(GPU& _gpu) noexcept;

		virtual void load() override;
		virtual void unload() override;

		void per_frame(const Vector4<>& _sun_dir, const Color<>& _sun_color, const Color<>& _ambient_color) const;
		void per_object(const Mesh& _mesh, const Material::Lambert& _mat) const;

	private:
		bgfx::UniformHandle u_s_tex_color_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_mat_color_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_light_dir_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_ambient_color_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_light_color_ = {bgfx::kInvalidHandle};
	};
}
