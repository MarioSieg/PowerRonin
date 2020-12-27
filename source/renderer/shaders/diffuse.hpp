#pragma once

#include "../ishader.hpp"

namespace dce::renderer::shaders {
	class DiffuseShader final : public IShader<Material::Diffuse> {
	public:
		explicit DiffuseShader(GPU& _gpu) noexcept;

		void load() override;
		void unload() override;
		void draw(const Material::Diffuse& _mat, const Mesh& _mesh) const override;

	private:
		bgfx::UniformHandle u_s_tex_color_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_mat_color_ = {bgfx::kInvalidHandle};
	};
}
