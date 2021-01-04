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

#include "skybox.hpp"

namespace power_ronin::renderer::shaders
{
	SkyboxShader::SkyboxShader(GPU& _gpu) noexcept : IShader("skybox", _gpu) { }

	void SkyboxShader::load()
	{
		IShader::load();
		this->cubemap_sampler_.load();
	}

	void SkyboxShader::unload()
	{
		this->cubemap_sampler_.unload();
		IShader::unload();
	}

	void SkyboxShader::draw(const Material::StaticSkybox& _mat, const Mesh& _mesh) const
	{
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.cubemap, this->cubemap_sampler_, 0);
		this->gpu_.draw(this->program_, SKYBOX_VIEW, BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_LESS);
	}
}
