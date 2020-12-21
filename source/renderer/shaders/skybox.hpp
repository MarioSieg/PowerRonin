#pragma once

#include "../ishader.hpp"

namespace dce::renderer::shaders {

	class Skybox final : public IShader {
	public:
		explicit Skybox(GPU& _gpu) noexcept;

		void load() override;
		void unload() override;
		void per_frame(const Texture& _skybox, const Mesh& _skydome) const;

	private:
		bgfx::UniformHandle u_s_tex_cube_ = {bgfx::kInvalidHandle};
	};
}
