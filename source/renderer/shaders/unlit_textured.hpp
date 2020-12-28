#pragma once

#include "../ishader.hpp"

namespace dce::renderer::shaders {
	class UnlitTexturedShader final : public IShader<Material::UnlitTextured> {
	public:
		explicit UnlitTexturedShader(GPU& _gpu) noexcept;

		void load() override;
		void unload() override;
		void draw(const Material::UnlitTextured& _mat, const Mesh& _mesh) const;

	private:
		bgfx::UniformHandle u_s_tex_color_ = {bgfx::kInvalidHandle};
	};
}
