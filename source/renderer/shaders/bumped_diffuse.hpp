#pragma once

#include "../ishader.hpp"

namespace dce::renderer::shaders {
	class BumpedDiffuseShader final : public IShader<Material::BumpedDiffuse> {
	public:
		explicit BumpedDiffuseShader(GPU& _gpu) noexcept;

		void load() override;
		void unload() override;
		void draw(const Material::BumpedDiffuse& _type, const Mesh& _mesh) const override;

	private:
		bgfx::UniformHandle u_s_tex_color_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_s_normal_map_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_mat_color_ = {bgfx::kInvalidHandle};
	};
}
