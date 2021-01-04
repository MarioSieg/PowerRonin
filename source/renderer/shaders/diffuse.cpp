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

#include "diffuse.hpp"

namespace power_ronin::renderer::shaders
{
	DiffuseShader::DiffuseShader(GPU& _gpu) noexcept : IShader("diffuse", _gpu) { }

	void DiffuseShader::load()
	{
		IShader::load();
		this->diffuse_texture_sampler_.load();
		this->tiling_offset_.load();
	}

	void DiffuseShader::unload()
	{
		this->tiling_offset_.unload();
		this->diffuse_texture_sampler_.unload();
		IShader::unload();
	}

	void DiffuseShader::draw(const Material::Diffuse& _mat, const Mesh& _mesh) const
	{
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.albedo, this->diffuse_texture_sampler_, 0);
		this->tiling_offset_.set(_mat.tiling_offset);
		this->gpu_.draw(this->program_, SCENERY_VIEW);
	}
}
