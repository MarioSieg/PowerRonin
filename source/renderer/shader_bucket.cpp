// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: shader_bucket.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 19.11.2020 19:03

#include "shader_bucket.hpp"
#include <variant>

namespace dce::renderer {
	ShaderBucket::ShaderBucket(GPU &_gpu) noexcept : unlit_(_gpu), lambert_(_gpu) { }

	void ShaderBucket::load_all() {
		this->unlit_.load();
		this->lambert_.load();
	}

	void ShaderBucket::unload_all() {
		this->lambert_.unload();
		this->unlit_.unload();
	}

	void ShaderBucket::per_frame(const PerFrameBuffer &_buffer) {
		this->unlit_.per_frame(_buffer);
		this->lambert_.per_frame(_buffer);
	}

	void ShaderBucket::per_material(const PerMaterialBuffer &_buffer) {
		this->unlit_.per_material(_buffer);
		this->lambert_.per_material(_buffer);
	}

	void ShaderBucket::per_object(const PerObjectBuffer &_buffer) {
		this->unlit_.per_object(_buffer);
		this->lambert_.per_object(_buffer);
	}

	void ShaderBucket::render(GPU &_gpu, const MeshRenderer &_renderer) {
		if (std::holds_alternative<Material::Unlit>(_renderer.material.properties)) {
			this->unlit_.draw(_renderer.mesh, std::get<Material::Unlit>(_renderer.material.properties));
		}
		else if (std::holds_alternative<Material::Lambert>(_renderer.material.properties)) {
			this->lambert_.draw(_renderer.mesh, std::get<Material::Lambert>(_renderer.material.properties));
		}
	}
}
