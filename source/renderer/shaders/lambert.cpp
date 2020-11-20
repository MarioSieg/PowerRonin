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

	Lambert::Lambert() noexcept : IShader("lambert") { }

	void Lambert::load() {
		IShader::load();
		this->u_s_tex_color_ = createUniform("s_tex_color", bgfx::UniformType::Sampler);
		this->u_color_ = createUniform("u_color", bgfx::UniformType::Vec4);
		this->u_light_dir_ = createUniform("u_light_dir", bgfx::UniformType::Vec4);
	}

	void Lambert::draw(GPU &_gpu, const Mesh &_mesh, const Material::Lambert &_mat, const Vector4<> &_args) {
		_gpu.set_uniform(this->u_light_dir_, _args);
		_gpu.set_uniform(this->u_color_, _mat.color);
		_gpu.set_mesh_buffer(_mesh);
		_gpu.set_texture(_mat.albedo, this->u_s_tex_color_);
		_gpu.draw(this->program_);
	}

	void Lambert::unload() {
		BGFX_FREE(this->u_light_dir_)
		BGFX_FREE(this->u_color_)
		BGFX_FREE(this->u_s_tex_color_)
		IShader::unload();
	}
}
