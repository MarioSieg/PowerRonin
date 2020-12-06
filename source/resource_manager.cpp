// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../include/dce/resource_manager.hpp"

namespace dce {
	void SystemResources::load_all(ResourceManager& _importeur) {
		this->empty_black_1x1 = _importeur.load<Texture>(std::filesystem::absolute("textures/common/unit/black.png"));
		this->empty_white_1x1 = _importeur.load<Texture>(std::filesystem::absolute("textures/common/unit/white.png"));
		this->empty_normal_1x1 = _importeur.load<Texture>(std::filesystem::absolute("textures/common/unit/normal.png"));
		this->empty_pbr_1x1 = _importeur.load<Texture>(std::filesystem::absolute("textures/common/unit/pbr.png"));
		this->error_marker = _importeur.load<Texture>(std::filesystem::absolute("textures/common/invalid.dds"));
		this->checkerboard = _importeur.load<Texture>(std::filesystem::absolute("textures/common/checkerboard.dds"));
		this->error_text = _importeur.load<Mesh>(std::filesystem::absolute("meshes/common/invalid.obj"));
		this->cube = _importeur.load<Mesh>(std::filesystem::absolute("meshes/common/cube.obj"));
		this->skydome = _importeur.load<Mesh>(std::filesystem::absolute("meshes/common/skydome.obj"));
		this->skybox = _importeur.load<Texture>(std::filesystem::absolute("textures/skybox/wispy.dds"));
	}

	auto ResourceManager::get_texture_cache() const noexcept -> const ResourceCache<Texture>& {
		return this->texture_cache_;
	}

	auto ResourceManager::get_mesh_cache() const noexcept -> const ResourceCache<Mesh>& {
		return this->mesh_cache_;
	}

	auto ResourceManager::get_material_cache() const noexcept -> const ResourceCache<Material>& {
		return this->material_cache_;
	}

	auto ResourceManager::get_audio_clip_cache() const noexcept -> const ResourceCache<AudioClip>& {
		return this->audio_clip_cache_;
	}

	void ResourceManager::unload_all_resources() {
		this->texture_cache_.clear();
		this->mesh_cache_.clear();
		this->material_cache_.clear();
		this->audio_clip_cache_.clear();
	}

	auto ResourceManager::load_texture(std::filesystem::path&& _file, const TextureMeta* const _meta) -> RRef<Texture> {
		const auto id = HString(_file.string().c_str());
		return this->texture_cache_.load<TextureImporteur>(id, std::move(_file));
	}

	auto ResourceManager::load_mesh(std::filesystem::path&& _file, const MeshMeta* const _meta) -> RRef<Mesh> {
		const auto id = HString(_file.string().c_str());
		return this->mesh_cache_.load<MeshImporteur>(id, std::move(_file));
	}

	auto ResourceManager::load_material(std::filesystem::path&& _file, const MaterialMeta* const _meta) -> RRef<Material> {
		const auto id = HString(_file.string().c_str());
		return this->material_cache_.load<MaterialImporteur>(id, std::move(_file));
	}

	auto ResourceManager::load_audio_clip(std::filesystem::path&& _file, const AudioClipMeta* const _meta) -> RRef<AudioClip> {
		const auto id = HString(_file.string().c_str());
		return this->audio_clip_cache_.load<AudioClipImporteur>(id, std::move(_file));
	}
} // namespace dce // namespace dce
