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
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "unlit.hpp"

namespace dce::renderer::shaders {
	Unlit::Unlit(GPU& _gpu) noexcept : IShader("unlit", _gpu) { }

	void Unlit::load() {
		IShader::load();
		this->u_s_tex_color_ = createUniform("s_tex_color", bgfx::UniformType::Sampler);
	}

	void Unlit::unload() {
		BGFX_FREE(this->u_s_tex_color_)
		IShader::unload();
	}

	void Unlit::per_object(const Mesh& _mesh, const Material::Unlit& _mat) const {
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.albedo, this->u_s_tex_color_, 0);
		this->gpu_.draw(this->program_, SCENERY_VIEW);
	}
}
