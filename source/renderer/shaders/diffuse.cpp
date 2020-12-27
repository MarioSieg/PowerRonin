#include "diffuse.hpp"

namespace dce::renderer::shaders {
	DiffuseShader::DiffuseShader(GPU& _gpu) noexcept : IShader("diffuse", _gpu) {
	}

	void DiffuseShader::load() {
		IShader::load();
		this->u_s_tex_color_ = createUniform("s_tex_color", bgfx::UniformType::Sampler);
		this->u_s_tex_color_ = createUniform("s_normal_map", bgfx::UniformType::Sampler);
		this->u_mat_color_ = createUniform("u_mat_color", bgfx::UniformType::Vec4);
	}

	void DiffuseShader::unload() {
		destroy(this->u_mat_color_);
		destroy(this->u_s_tex_color_);
		IShader::unload();
	}

	void DiffuseShader::draw(const Material::Diffuse& _mat, const Mesh& _mesh) const {
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.albedo, this->u_s_tex_color_, 0);
		this->gpu_.draw(this->program_, SCENERY_VIEW);
	}
}
