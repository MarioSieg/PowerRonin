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
		this->system_resources.textures.black_1x1 = this->texture_cache.load<TextureImporteur>(
			this->gen_id(), "textures/common/unit/black.png");
		this->system_resources.textures.white_1x1 = this->texture_cache.load<TextureImporteur>(
			this->gen_id(), "textures/common/unit/white.png");
		this->system_resources.textures.error_marker = this->texture_cache.load<TextureImporteur>(
			this->gen_id(), "textures/common/invalid.dds");
		this->system_resources.textures.checkerboard = this->texture_cache.load<TextureImporteur>(
			this->gen_id(), "textures/common/checkerboard.dds");

		this->system_resources.meshes.error_text = this->mesh_cache.load<MeshImporteur>(
			this->gen_id(), "meshes/common/invalid.obj");
		this->system_resources.meshes.cube = this->mesh_cache.load<MeshImporteur>(this->gen_id(), "meshes/common/cube.obj");

		std::unordered_map<std::string_view, std::tuple<UniformType, std::uint16_t>> uniforms = {
			{"s_texColor", std::make_tuple(UniformType::SAMPLER, 0)}
		};

		this->system_resources.shaders.unlit = this->shader_cache.load<ShaderImporteur>(
			this->gen_id(), "shaders/bin/unlit/dx11/vertex.shc", std::move(uniforms));
	}
} // namespace dce // namespace dce
