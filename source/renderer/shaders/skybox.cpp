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

#include "skybox.hpp"

namespace dce::renderer::shaders {

	Skybox::Skybox(GPU& _gpu) noexcept : IShader("skybox", _gpu) { }

	void Skybox::load() {
		IShader::load();
		this->u_s_tex_cube_ = createUniform("s_tex_cube", bgfx::UniformType::Sampler);
	}

	void Skybox::unload() {
		BGFX_FREE(this->u_s_tex_cube_)
		IShader::unload();
	}

	void Skybox::per_frame(const Texture& _skybox, const Mesh& _skydome) const {
		this->gpu_.set_mesh_buffer(_skydome);
		this->gpu_.set_texture(_skybox, this->u_s_tex_cube_, 0);
		this->gpu_.draw(this->program_, SKYBOX_VIEW, BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_LESS);
	}
}
