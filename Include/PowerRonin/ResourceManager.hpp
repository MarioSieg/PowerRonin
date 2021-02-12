#pragma once

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Material.hpp"

namespace PowerRonin
{
	class AsyncProtocol;
	class ResourceManager;

	/// <summary>
	/// Contains all resources needed by the engine.
	/// </summary>
	struct SystemResources final
	{
		RRef<Texture> EmptyBlack1X1 = {};
		RRef<Texture> EmptyWhite1X1 = {};
		RRef<Texture> EmptyNormal1X1 = {};
		RRef<Texture> EmptyPbr1X1 = {};
		RRef<Texture> ErrorMarker = {};
		RRef<Texture> Checkerboard = {};
		RRef<Mesh> ErrorText = {};
		RRef<Mesh> Cube = {};
		RRef<Mesh> SkyDome = {};
		RRef<Texture> SkyBox = {};

		void LoadAll(ResourceManager& resourceManager);
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
		SystemResources SystemResources = {};

		/// <summary>
		/// 
		/// </summary>
		/// <returns>An immutable reference to the global texture cache.</returns>
		[[nodiscard]] auto TextureCache() const noexcept -> const ResourceCache<Texture>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>An immutable reference to the global mesh cache.</returns>
		[[nodiscard]] auto MeshCache() const noexcept -> const ResourceCache<Mesh>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>An immutable reference to the global material cache.</returns>
		[[nodiscard]] auto MaterialCache() const noexcept -> const ResourceCache<Material>&;

		/// <summary>
		/// Loads a resource of type T from a file and stores it in the corresponding resource cache.
		/// </summary>
		/// <typeparam name="T">The type to load. For example Texture or Mesh.</typeparam>
		/// <param name="file">The file path to the file to be loaded.</param>
		/// <returns>A resource reference to the newly loaded resource.</returns>
		template <typename T> requires std::is_base_of_v<IResource<typename T::Meta>, T>
		[[nodiscard]] auto Load(std::filesystem::path&& file) -> RRef<T>;

		/// <summary>
		/// Loads a resource of type T from a file and stores it in the corresponding resource cache but with metadata.
		/// </summary>
		/// <typeparam name="T"><The type to load. For example Texture or Mesh./typeparam>
		/// <param name="file">The file path to the file to be loaded.</param>
		/// <param name="meta">The metadata pointer. Pass nullptr to load it from file.</param>
		/// <returns>A resource reference to the newly loaded resource.</returns>
		template <typename T> requires std::is_base_of_v<IResource<typename T::Meta>, T>
		[[nodiscard]] auto Load(std::filesystem::path&& file, const typename T::Meta* const meta) -> RRef<T>;

		/// <summary>
		/// Destroys all resources. (!DANGEROUS!)
		/// </summary>
		void UnloadAllResources();

	private:
		[[nodiscard]] auto LoadTexture(std::filesystem::path&& file, const TextureMeta* const meta) -> RRef<Texture>;
		[[nodiscard]] auto LoadMesh(std::filesystem::path&& file, const MeshMeta* const meta) -> RRef<Mesh>;
		[[nodiscard]] auto LoadMaterial(std::filesystem::path&& file, const MaterialMeta* const meta) -> RRef<Material>;

		AsyncProtocol& proto;
		ResourceCache<Texture> textureCache = {};
		ResourceCache<Mesh> meshCache = {};
		ResourceCache<Material> materialCache = {};
	};

	template <>
	inline auto ResourceManager::Load(std::filesystem::path&& _file) -> RRef<Texture>
	{
		return this->LoadTexture(std::move(_file), nullptr);
	}

	template <>
	inline auto ResourceManager::Load(std::filesystem::path&& _file) -> RRef<Mesh>
	{
		return this->LoadMesh(std::move(_file), nullptr);
	}

	template <>
	inline auto ResourceManager::Load(std::filesystem::path&& _file) -> RRef<Material>
	{
		return this->LoadMaterial(std::move(_file), nullptr);
	}

	template <>
	inline auto ResourceManager::Load(std::filesystem::path&& _file, const TextureMeta* const _meta) -> RRef<Texture>
	{
		return this->LoadTexture(std::move(_file), _meta);
	}

	template <>
	inline auto ResourceManager::Load(std::filesystem::path&& _file, const MeshMeta* const _meta) -> RRef<Mesh>
	{
		return this->LoadMesh(std::move(_file), _meta);
	}

	template <>
	inline auto ResourceManager::Load(std::filesystem::path&& _file,
	                                  const MaterialMeta* const _meta) -> RRef<Material>
	{
		return this->LoadMaterial(std::move(_file), _meta);
	}
} // namespace PowerRonin // namespace PowerRonin
