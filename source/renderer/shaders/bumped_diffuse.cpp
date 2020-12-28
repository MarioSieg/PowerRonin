#include "bumped_diffuse.hpp"

namespace dce::renderer::shaders {
	BumpedDiffuseShader::BumpedDiffuseShader(GPU& _gpu) noexcept : IShader("bumped_diffuse", _gpu) {
	}

	void BumpedDiffuseShader::load() {
		IShader::load();
		this->u_s_tex_color_ = createUniform("s_tex_color", bgfx::UniformType::Sampler);
		this->u_s_normal_map_ = createUniform("s_normal_map", bgfx::UniformType::Sampler);
		this->u_mat_color_ = createUniform("u_mat_color", bgfx::UniformType::Vec4);
	}

	void BumpedDiffuseShader::unload() {
		destroy(this->u_mat_color_);
		destroy(this->u_s_normal_map_);
		destroy(this->u_s_tex_color_);
		IShader::unload();
	}

	void BumpedDiffuseShader::draw(const Material::BumpedDiffuse& _mat, const Mesh& _mesh) const {
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.albedo, this->u_s_tex_color_, 0);
		this->gpu_.set_texture(_mat.normal, this->u_s_normal_map_, 1);
		this->gpu_.draw(this->program_, SCENERY_VIEW);
	}

	void BumpedDiffuseShader::draw(const Material::BumpedDiffuse& _mat, const Mesh& _mesh, const bgfx::OcclusionQueryHandle _oqh) const {
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.albedo, this->u_s_tex_color_, 0);
		this->gpu_.set_texture(_mat.normal, this->u_s_normal_map_, 1);
		this->gpu_.draw(this->program_, SCENERY_VIEW, _oqh);
	}
}
