// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: unlit.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 19.11.2020 18:32

#include "unlit.hpp"

namespace dce::renderer {

	Unlit::Unlit(GPU &_gpu) noexcept : IShader("unlit", _gpu) {}

	void Unlit::load() {
		IShader::load();
		this->u_s_tex_color_ = createUniform("s_tex_color", bgfx::UniformType::Sampler);
	}

	void Unlit::unload() {
		BGFX_FREE(this->u_s_tex_color_)
		IShader::unload();
	}

	void Unlit::draw(const Mesh &_mesh, const Material::Unlit &_mat) {
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.albedo, this->u_s_tex_color_);
		this->gpu_.draw(this->program_);
	}
}
