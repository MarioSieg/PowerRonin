#pragma once

#include "../ishader.hpp"

namespace PowerRonin::Renderer::Shaders
{
	class SkyboxShader final : public IShader<Material::StaticSkybox>
	{
	public:
		explicit SkyboxShader(GPU& _gpu) noexcept;

		virtual void load() override;
		virtual void unload() override;
		void draw(const Material::StaticSkybox& _mat, const Mesh& _mesh) const;

	private:
		Uniform cubemap_sampler_ = {"s_tex_cube", bgfx::UniformType::Sampler};
	};
}
