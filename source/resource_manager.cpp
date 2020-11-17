// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: resource_manager.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "../include/dce/resource_manager.hpp"

namespace dce {
	void ResourceManager::load_system_resources() {
		this->system_resources.black_texture = this->texture_cache.load<TextureImporteur>(
			this->gen_id(), "textures/common/unit/black.png");
		this->system_resources.white_texture = this->texture_cache.load<TextureImporteur>(
			this->gen_id(), "textures/common/unit/white.png");
		this->system_resources.invalid_texture = this->texture_cache.load<TextureImporteur>(
			this->gen_id(), "textures/common/invalid.dds");
		this->system_resources.checkerboard_texture = this->texture_cache.load<TextureImporteur>(
			this->gen_id(), "textures/common/checkerboard.dds");

		this->system_resources.error_mesh = this->mesh_cache.load<MeshImporteur>(this->gen_id(), "meshes/common/invalid.obj");
		this->system_resources.basic_shader = this->shader_cache.load<ShaderImporteur>(
			this->gen_id(), "shaders/bin/dx11/mesh.cshader");
	}
} // namespace dce // namespace dce
