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

	void ShaderBucket::load_all() {
		this->unlit_.load();
		this->lambert_.load();
	}

	void ShaderBucket::unload_all() {
		this->lambert_.unload();
		this->unlit_.unload();
	}

	void ShaderBucket::render(GPU &_gpu, const MeshRenderer &_renderer, const RenderParams &_props) {
		if (std::holds_alternative<Material::Unlit>(_renderer.material.properties)) {
			this->unlit_.draw(_gpu, _renderer.mesh, std::get<Material::Unlit>(_renderer.material.properties));
		}
		else if (std::holds_alternative<Material::Lambert>(_renderer.material.properties)) {
			this->lambert_.draw(_gpu, _renderer.mesh, std::get<Material::Lambert>(_renderer.material.properties)
			                    , _props.light_dir);
		}
	}
}
