#include "diffuse.hpp"

namespace dce::renderer::shaders {
	Diffuse::Diffuse(GPU& _gpu) noexcept : IShader("diffuse", _gpu) {
	}

	void Diffuse::load() {
		IShader::load();
		this->u_s_tex_color_ = createUniform("s_tex_color", bgfx::UniformType::Sampler);
		this->u_s_tex_color_ = createUniform("s_normal_map", bgfx::UniformType::Sampler);
		this->u_mat_color_ = createUniform("u_mat_color", bgfx::UniformType::Vec4);
		this->u_light_dir_ = createUniform("u_light_dir", bgfx::UniformType::Vec4);
		this->u_ambient_color_ = createUniform("u_ambient_color", bgfx::UniformType::Vec4);
		this->u_light_color_ = createUniform("u_light_color", bgfx::UniformType::Vec4);
	}

	void Diffuse::unload() {
		destroy(this->u_light_color_);
		destroy(this->u_ambient_color_);
		destroy(this->u_light_dir_);
		destroy(this->u_mat_color_);
		destroy(this->u_s_tex_color_);
		IShader::unload();
	}

	void Diffuse::per_frame(const Vector4<>& _sun_dir, const Color<>& _sun_color, const Color<>& _ambient_color) const {
		this->gpu_.set_uniform(this->u_light_dir_, _sun_dir);
		this->gpu_.set_uniform(this->u_light_color_, _sun_color);
		this->gpu_.set_uniform(this->u_ambient_color_, _ambient_color);
	}

	void Diffuse::per_object(const Mesh& _mesh, const Material::Diffuse& _mat) const {
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.albedo, this->u_s_tex_color_, 0);
		this->gpu_.draw(this->program_, SCENERY_VIEW);
	}
}
