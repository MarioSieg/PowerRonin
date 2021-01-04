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

namespace power_ronin::renderer::shaders
{
	class SkyboxShader final : public IShader<Material::StaticSkybox>
	{
	public:
		explicit SkyboxShader(GPU& _gpu) noexcept;

		void load() override;
		void unload() override;
		void draw(const Material::StaticSkybox& _mat, const Mesh& _mesh) const;

	private:
		Uniform cubemap_sampler_ = {"s_tex_cube", bgfx::UniformType::Sampler};
	};
}
