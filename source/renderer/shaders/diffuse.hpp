#pragma once

#include "../ishader.hpp"

namespace PowerRonin::Renderer::Shaders
{
	class DiffuseShader final : public IShader<Material::Diffuse>
	{
	public:
		explicit DiffuseShader(GPU& _gpu) noexcept;

		virtual void load() override;
		virtual void unload() override;
		void draw(const Material::Diffuse& _mat, const Mesh& _mesh) const;

	private:
		Uniform diffuse_texture_sampler_ = {"s_tex_color", bgfx::UniformType::Sampler};
		Uniform tiling_offset_ = {"u_tiling_offset", bgfx::UniformType::Vec4};
	};
}
