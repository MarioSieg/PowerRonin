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

#include "../ishader.hpp"

namespace PowerRonin::Renderer::Shaders
{
	class BumpedDiffuseShader final : public IShader<Material::BumpedDiffuse>
	{
	public:
		explicit BumpedDiffuseShader(GPU& _gpu) noexcept;

		void load() override;
		void unload() override;
		void draw(const Material::BumpedDiffuse& _mat, const Mesh& _mesh) const;

	private:
		Uniform diffuse_texture_sampler_ = {"s_tex_color", bgfx::UniformType::Sampler};
		Uniform normal_map_sampler_ = {"s_normal_map", bgfx::UniformType::Sampler};
		Uniform tiling_offset_ = {"u_tiling_offset", bgfx::UniformType::Vec4};
	};
}
