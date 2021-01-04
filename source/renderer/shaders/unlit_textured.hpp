#pragma once

#include "../ishader.hpp"

namespace power_ronin::renderer::shaders
{
	class UnlitTexturedShader final : public IShader<Material::UnlitTextured>
	{
	public:
		explicit UnlitTexturedShader(GPU& _gpu) noexcept;

		void load() override;
		void unload() override;
		void draw(const Material::UnlitTextured& _mat, const Mesh& _mesh) const;

	private:
		Uniform texture_sampler_ = {"s_tex_color", bgfx::UniformType::Sampler};
		Uniform tiling_offset_ = {"u_tiling_offset", bgfx::UniformType::Vec4};
	};
}
