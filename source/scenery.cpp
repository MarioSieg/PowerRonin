#include "../include/dce/scenery.hpp"
#include "../include/dce/resource_manager.hpp"

namespace dce {
	auto Scenery::registry() const noexcept -> const Registry& {
		return this->registry_;
	}

	auto Scenery::registry() noexcept -> Registry& {
		return this->registry_;
	}

	void Scenery::initialize() {
	}

	void Scenery::new_default(ResourceManager& _resource_manager) {
		// Create cube:
		{
			const auto cube = this->registry_.create();

			auto& meta = this->registry_.emplace<MetaData>(cube);
			auto& transform = this->registry_.emplace<Transform>(cube);
			auto& renderer = this->registry_.emplace<MeshRenderer>(cube);
			auto& collider = this->registry_.emplace<Collider>(cube);

			meta.name = "Cube";
			Material::BumpedDiffuse lambert;
			lambert.albedo = _resource_manager.load<Texture>("examples/snow_albedo.dds");
			lambert.normal = _resource_manager.load<Texture>("examples/snow_normal.dds");
			renderer.material = Material::create_from_data(lambert, "cube", _resource_manager);
			renderer.mesh = _resource_manager.system_resources.cube;
		}

		// Create platform:
		{
			const auto platform = this->registry_.create();

			auto& meta = this->registry_.emplace<MetaData>(platform);
			auto& transform = this->registry_.emplace<Transform>(platform);
			auto& renderer = this->registry_.emplace<MeshRenderer>(platform);

			meta.name = "Platform";
			transform.position.y = -1.f;
			transform.scale *= 3.f;
			Material::Diffuse lambert;
			lambert.albedo = _resource_manager.system_resources.checkerboard;
			renderer.material = Material::create_from_data(lambert, "platform", _resource_manager);
			renderer.mesh = _resource_manager.load<Mesh>("meshes/common/platform.obj");
		}

		TextureMeta skybox_cubemap_meta = {};
		skybox_cubemap_meta.sampler_flags = SamplerFlags::UVW_CLAMP;

		// Load skybox:
		this->config.lighting.skybox_cubemap = _resource_manager.system_resources.skybox;
		this->config.lighting.skydome = _resource_manager.system_resources.skydome;
	}

	void Scenery::unload_all_entities() {
		this->registry_.clear();
	}
} // namespace dce
