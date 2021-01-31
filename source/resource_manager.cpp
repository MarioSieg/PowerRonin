// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#include "../include/power_ronin/resource_manager.hpp"
#include "../include/power_ronin/proto.hpp"

namespace PowerRonin
{
	void SystemResources::LoadAll(ResourceManager& resourceManager)
	{
		resourceManager.proto.Info("Loading system resources...");

		auto texture_meta = TextureMeta{};
		auto mesh_meta = MeshMeta{};

		this->EmptyBlack1X1 = resourceManager.Load<Texture>(std::filesystem::absolute("textures/common/unit/black.png"),
		                                          &texture_meta);
		this->EmptyWhite1X1 = resourceManager.Load<Texture>(std::filesystem::absolute("textures/common/unit/white.png"),
		                                          &texture_meta);
		this->EmptyNormal1X1 = resourceManager.Load<Texture>(std::filesystem::absolute("textures/common/unit/normal.png"),
		                                           &texture_meta);
		this->EmptyPbr1X1 = resourceManager.Load<Texture>(std::filesystem::absolute("textures/common/unit/pbr.png"),
		                                        &texture_meta);
		this->ErrorMarker = resourceManager.Load<Texture>(std::filesystem::absolute("textures/common/invalid.dds"), &texture_meta);
		this->Checkerboard = resourceManager.Load<Texture>(std::filesystem::absolute("textures/common/checkerboard.dds"),
		                                       &texture_meta);
		this->SkyBox = resourceManager.Load<Texture>(std::filesystem::absolute("textures/skybox/default.dds"), &texture_meta);

		this->ErrorText = resourceManager.Load<Mesh>(std::filesystem::absolute("meshes/common/invalid.obj"), &mesh_meta);
		this->Cube = resourceManager.Load<Mesh>(std::filesystem::absolute("meshes/common/cube.obj"), &mesh_meta);
		this->SkyDome = resourceManager.Load<Mesh>(std::filesystem::absolute("meshes/common/skydome.obj"), &mesh_meta);

		resourceManager.proto.Info("System resources loaded!");
	}

	ResourceManager::ResourceManager(AsyncProtocol& _proto) noexcept : proto(_proto) { }

	auto ResourceManager::TextureCache() const noexcept -> const ResourceCache<Texture>&
	{
		return this->textureCache;
	}

	auto ResourceManager::MeshCache() const noexcept -> const ResourceCache<Mesh>&
	{
		return this->meshCache;
	}

	auto ResourceManager::MaterialCache() const noexcept -> const ResourceCache<Material>&
	{
		return this->materialCache;
	}

	void ResourceManager::UnloadAllResources()
	{
		this->textureCache.clear();
		this->meshCache.clear();
		this->materialCache.clear();
	}

	auto ResourceManager::LoadTexture(std::filesystem::path&& file, const TextureMeta* const meta) -> RRef<Texture>
	{
		const auto fileName = file.filename().string();
		const auto id = HashedString(fileName.c_str());
		auto ptr = this->textureCache.load<TextureImporteur>(id, std::move(file), meta);
		return ptr;
	}

	auto ResourceManager::LoadMesh(std::filesystem::path&& file, const MeshMeta* const meta) -> RRef<Mesh>
	{
		const auto id = HashedString(file.string().c_str());
		auto ptr = this->meshCache.load<MeshImporteur>(id, std::move(file), meta);
		return ptr;
	}

	auto ResourceManager::LoadMaterial(std::filesystem::path&& file,
	                                    const MaterialMeta* const meta) -> RRef<Material>
	{
		const auto id = HashedString(file.string().c_str());
		auto ptr = this->materialCache.load<MaterialImporteur>(id, std::move(file), meta);
		return ptr;
	}
} // namespace PowerRonin // namespace PowerRonin
