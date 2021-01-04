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

#pragma once

#include "mesh.hpp"
#include "texture.hpp"
#include "material.hpp"

namespace power_ronin
{
	class AsyncProtocol;
	class ResourceManager;

	/// <summary>
	/// Contains all resources needed by the engine.
	/// </summary>
	struct SystemResources final
	{
		RRef<Texture> empty_black_1x1 = {};
		RRef<Texture> empty_white_1x1 = {};
		RRef<Texture> empty_normal_1x1 = {};
		RRef<Texture> empty_pbr_1x1 = {};
		RRef<Texture> error_marker = {};
		RRef<Texture> checkerboard = {};
		RRef<Mesh> error_text = {};
		RRef<Mesh> cube = {};
		RRef<Mesh> skydome = {};
		RRef<Texture> skybox = {};

		void load_all(ResourceManager& _rm);
	};

	/// <summary>
	/// Manager of all resources like textures or meshes.
	/// </summary>
	class ResourceManager final
	{
		friend SystemResources;
	public:
		explicit ResourceManager(AsyncProtocol& _proto) noexcept;
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		auto operator=(const ResourceManager&) -> ResourceManager& = delete;
		auto operator=(ResourceManager&&) -> ResourceManager& = delete;
		~ResourceManager() = default;

		/// <summary>
		/// Build in system resources.
		/// </summary>
		SystemResources system_resources = {};

		/// <summary>
		/// 
		/// </summary>
		/// <returns>An immutable reference to the global texture cache.</returns>
		[[nodiscard]] auto texture_cache() const noexcept -> const ResourceCache<Texture>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>An immutable reference to the global mesh cache.</returns>
		[[nodiscard]] auto mesh_cache() const noexcept -> const ResourceCache<Mesh>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>An immutable reference to the global material cache.</returns>
		[[nodiscard]] auto material_cache() const noexcept -> const ResourceCache<Material>&;

		/// <summary>
		/// Loads a resource of type T from a file and stores it in the corresponding resource cache.
		/// </summary>
		/// <typeparam name="T">The type to load. For example Texture or Mesh.</typeparam>
		/// <param name="_file">The file path to the file to be loaded.</param>
		/// <returns>A resource reference to the newly loaded resource.</returns>
		template <typename T> requires std::is_base_of_v<IResource<typename T::Meta>, T>
		[[nodiscard]] auto load(std::filesystem::path&& _file) -> RRef<T>;

		/// <summary>
		/// Loads a resource of type T from a file and stores it in the corresponding resource cache but with metadata.
		/// </summary>
		/// <typeparam name="T"><The type to load. For example Texture or Mesh./typeparam>
		/// <param name="_file">The file path to the file to be loaded.</param>
		/// <param name="_meta">The metadata pointer. Pass nullptr to load it from file.</param>
		/// <returns>A resource reference to the newly loaded resource.</returns>
		template <typename T> requires std::is_base_of_v<IResource<typename T::Meta>, T>
		[[nodiscard]] auto load(std::filesystem::path&& _file, const typename T::Meta* const _meta) -> RRef<T>;

		/// <summary>
		/// Destroys all resources. (!DANGEROUS!)
		/// </summary>
		void unload_all_resources();

	private:
		[[nodiscard]] auto load_texture(std::filesystem::path&& _file, const TextureMeta* const _meta) -> RRef<Texture>;
		[[nodiscard]] auto load_mesh(std::filesystem::path&& _file, const MeshMeta* const _meta) -> RRef<Mesh>;
		[[nodiscard]] auto load_material(std::filesystem::path&& _file, const MaterialMeta* const _meta) -> RRef<Material>;

		AsyncProtocol& proto_;
		ResourceCache<Texture> texture_cache_ = {};
		ResourceCache<Mesh> mesh_cache_ = {};
		ResourceCache<Material> material_cache_ = {};
	};

	template <>
	inline auto ResourceManager::load(std::filesystem::path&& _file) -> RRef<Texture>
	{
		return this->load_texture(std::move(_file), nullptr);
	}

	template <>
	inline auto ResourceManager::load(std::filesystem::path&& _file) -> RRef<Mesh>
	{
		return this->load_mesh(std::move(_file), nullptr);
	}

	template <>
	inline auto ResourceManager::load(std::filesystem::path&& _file) -> RRef<Material>
	{
		return this->load_material(std::move(_file), nullptr);
	}

	template <>
	inline auto ResourceManager::load(std::filesystem::path&& _file, const TextureMeta* const _meta) -> RRef<Texture>
	{
		return this->load_texture(std::move(_file), _meta);
	}

	template <>
	inline auto ResourceManager::load(std::filesystem::path&& _file, const MeshMeta* const _meta) -> RRef<Mesh>
	{
		return this->load_mesh(std::move(_file), _meta);
	}

	template <>
	inline auto ResourceManager::load(std::filesystem::path&& _file,
	                                  const MaterialMeta* const _meta) -> RRef<Material>
	{
		return this->load_material(std::move(_file), _meta);
	}
} // namespace power_ronin // namespace power_ronin
