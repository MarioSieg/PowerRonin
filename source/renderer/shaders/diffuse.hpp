#pragma once

#include "../ishader.hpp"

namespace dce::renderer::shaders {
	class DiffuseShader final : public IShader<Material::Diffuse> {
	public:
		explicit DiffuseShader(GPU& _gpu) noexcept;

		void load() override;
		void unload() override;
		void draw(const Material::Diffuse& _mat, const Mesh& _mesh) const;

	private:
		Uniform diffuse_texture_sampler_ = {"s_tex_color", bgfx::UniformType::Sampler};
		Uniform diffuse_color_ = {"u_mat_color", bgfx::UniformType::Vec4};
	};
}
