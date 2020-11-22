// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: lambert.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 20.11.2020 12:23

#include "lambert.hpp"

namespace dce::renderer {

	Lambert::Lambert(GPU& _gpu) noexcept : IShader("lambert", _gpu) { }

	void Lambert::load() {
		IShader::load();
		this->u_s_tex_color_ = createUniform("s_tex_color", bgfx::UniformType::Sampler);
		this->u_mat_color_ = createUniform("u_mat_color", bgfx::UniformType::Vec4);
		this->u_light_dir_ = createUniform("u_light_dir", bgfx::UniformType::Vec4);
		this->u_ambient_color = createUniform("u_ambient_color", bgfx::UniformType::Vec4);
		this->u_light_color = createUniform("u_light_color", bgfx::UniformType::Vec4);
	}

	void Lambert::draw(const Mesh& _mesh, const Material::Lambert& _mat) {
		this->gpu_.set_uniform(this->u_mat_color_, _mat.color);
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.albedo, this->u_s_tex_color_);
		this->gpu_.draw(this->program_);
	}

	void Lambert::unload() {
		BGFX_FREE(this->u_light_color);
		BGFX_FREE(this->u_ambient_color)
		BGFX_FREE(this->u_light_dir_)
		BGFX_FREE(this->u_mat_color_)
		BGFX_FREE(this->u_s_tex_color_)
		IShader::unload();
	}

	void Lambert::per_frame(const PerFrameBuffer& _buffer) {
		this->gpu_.set_uniform(this->u_light_dir_, _buffer.sun_dir);
		this->gpu_.set_uniform(this->u_ambient_color, _buffer.ambient_color);
		this->gpu_.set_uniform(this->u_light_color, _buffer.sun_color);
	}
}
