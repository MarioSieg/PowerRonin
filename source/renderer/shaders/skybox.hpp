#pragma once

#include "../ishader.hpp"

namespace dce::renderer::shaders
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
