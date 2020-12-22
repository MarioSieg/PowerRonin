#include "unlit_textured.hpp"

namespace dce::renderer::shaders {
	UnlitTextured::UnlitTextured(GPU& _gpu) noexcept : IShader("unlit_textured", _gpu) {
	}

	void UnlitTextured::load() {
		IShader::load();
		this->u_s_tex_color_ = createUniform("s_tex_color", bgfx::UniformType::Sampler);
	}

	void UnlitTextured::unload() {
		destroy(this->u_s_tex_color_);
		IShader::unload();
	}

	void UnlitTextured::per_object(const Mesh& _mesh, const Material::UnlitTextured& _mat) const {
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.albedo, this->u_s_tex_color_, 0);
		this->gpu_.draw(this->program_, SCENERY_VIEW);
	}
}
