#pragma once

#include "../ishader.hpp"

namespace dce::renderer::shaders {
	class BumpedDiffuseShader final : public IShader<Material::BumpedDiffuse> {
	public:
		explicit BumpedDiffuseShader(GPU& _gpu) noexcept;

		void load() override;
		void unload() override;
		void draw(const Material::BumpedDiffuse& _mat, const Mesh& _mesh) const;

	private:
		Uniform diffuse_texture_sampler_ = {"s_tex_color", bgfx::UniformType::Sampler};
		Uniform normal_map_sampler_ = {"s_normal_map", bgfx::UniformType::Sampler};
		Uniform diffuse_color_ = {"u_mat_color", bgfx::UniformType::Vec4};
	};
}
