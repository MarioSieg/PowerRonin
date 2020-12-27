#include "../include/dce/resource_manager.hpp"
#include "../include/dce/proto.hpp"

namespace dce {
	void SystemResources::load_all(ResourceManager& _rm) {
		_rm.proto_.info("Loading system resources...");

		auto texture_meta = TextureMeta{};
		auto mesh_meta = MeshMeta{};

		this->empty_black_1x1 = _rm.load<Texture>(std::filesystem::absolute("textures/common/unit/black.png"),
		                                          &texture_meta);
		this->empty_white_1x1 = _rm.load<Texture>(std::filesystem::absolute("textures/common/unit/white.png"),
		                                          &texture_meta);
		this->empty_normal_1x1 = _rm.load<Texture>(std::filesystem::absolute("textures/common/unit/normal.png"),
		                                           &texture_meta);
		this->empty_pbr_1x1 = _rm.load<Texture>(std::filesystem::absolute("textures/common/unit/pbr.png"),
		                                        &texture_meta);
		this->error_marker = _rm.load<Texture>(std::filesystem::absolute("textures/common/invalid.dds"), &texture_meta);
		this->checkerboard = _rm.load<Texture>(std::filesystem::absolute("textures/common/checkerboard.dds"),
		                                       &texture_meta);
		this->skybox = _rm.load<Texture>(std::filesystem::absolute("textures/skybox/default.dds"), &texture_meta);

		this->error_text = _rm.load<Mesh>(std::filesystem::absolute("meshes/common/invalid.obj"), &mesh_meta);
		this->cube = _rm.load<Mesh>(std::filesystem::absolute("meshes/common/cube.obj"), &mesh_meta);
		this->skydome = _rm.load<Mesh>(std::filesystem::absolute("meshes/common/skydome.obj"), &mesh_meta);

		_rm.proto_.info("System resources loaded!");
	}

	ResourceManager::ResourceManager(AsyncProtocol& _proto) noexcept : proto_(_proto) {
	}

	auto ResourceManager::texture_cache() const noexcept -> const ResourceCache<Texture>& {
		return this->texture_cache_;
	}

	auto ResourceManager::mesh_cache() const noexcept -> const ResourceCache<Mesh>& {
		return this->mesh_cache_;
	}

	auto ResourceManager::material_cache() const noexcept -> const ResourceCache<Material>& {
		return this->material_cache_;
	}

	void ResourceManager::unload_all_resources() {
		this->texture_cache_.clear();
		this->mesh_cache_.clear();
		this->material_cache_.clear();
	}

	auto ResourceManager::load_texture(std::filesystem::path&& _file, const TextureMeta* const _meta) -> RRef<Texture> {
		const auto state_clock = std::chrono::high_resolution_clock::now();
		const auto id = HString(_file.string().c_str());
		const auto file = _file.filename().string();
		auto ptr = this->texture_cache_.load<TextureImporteur>(id, std::move(_file), _meta);
		const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::high_resolution_clock::now() - state_clock).count()) / 1000000.0;
		this->proto_.critical("Loaded texture {} in {}s!", file, dur);
		return ptr;
	}

	auto ResourceManager::load_mesh(std::filesystem::path&& _file, const MeshMeta* const _meta) -> RRef<Mesh> {
		const auto state_clock = std::chrono::high_resolution_clock::now();
		const auto id = HString(_file.string().c_str());
		const auto file = _file.filename().string();
		auto ptr = this->mesh_cache_.load<MeshImporteur>(id, std::move(_file), _meta);
		const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::high_resolution_clock::now() - state_clock).count()) / 1000000.0;
		this->proto_.critical("Loaded mesh {} in {}s!", file, dur);
		return ptr;
	}

	auto ResourceManager::load_material(std::filesystem::path&& _file,
	                                    const MaterialMeta* const _meta) -> RRef<Material> {
		const auto state_clock = std::chrono::high_resolution_clock::now();
		const auto id = HString(_file.string().c_str());
		const auto file = _file.filename().string();
		auto ptr = this->material_cache_.load<MaterialImporteur>(id, std::move(_file), _meta);
		const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::high_resolution_clock::now() - state_clock).count()) / 1000000.0;
		this->proto_.critical("Loaded material {} in {}s!", file, dur);
		return ptr;
	}
} // namespace dce // namespace dce
