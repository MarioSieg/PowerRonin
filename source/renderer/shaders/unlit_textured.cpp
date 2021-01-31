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

#include "unlit_textured.hpp"

namespace PowerRonin::Renderer::Shaders
{
	UnlitTexturedShader::UnlitTexturedShader(GPU& _gpu) noexcept : IShader("unlit_textured", _gpu) { }

	void UnlitTexturedShader::load()
	{
		IShader::load();
		this->texture_sampler_.load();
		this->tiling_offset_.load();
	}

	void UnlitTexturedShader::unload()
	{
		this->tiling_offset_.unload();
		this->texture_sampler_.unload();
		IShader::unload();
	}

	void UnlitTexturedShader::draw(const Material::UnlitTextured& _mat, const Mesh& _mesh) const
	{
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.Albedo, this->texture_sampler_, 0);
		this->tiling_offset_.set(_mat.TilingOffset);
		this->gpu_.draw(this->program_, SCENERY_VIEW);
	}
}
