#pragma once

#include "../ishader.hpp"

namespace dce::renderer::shaders {
	class Unlit final : public IShader {
	public:
		explicit Unlit(GPU& _gpu) noexcept;

		void load() override;
		void unload() override;

		void per_object(const Mesh& _mesh, const Material::Unlit& _mat) const;

	private:
		bgfx::UniformHandle u_s_tex_color_ = {bgfx::kInvalidHandle};
	};
}
