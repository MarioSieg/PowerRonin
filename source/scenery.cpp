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
		for(auto i = 0; i < 128; ++i) {
			for(auto j = 0; j < 128; ++j) {
				const auto cube = this->registry_.create();

				auto& meta = this->registry_.emplace<MetaData>(cube);
				auto& transform = this->registry_.emplace<Transform>(cube);
				transform.position.x = i * 0.05F;
				transform.position.z = j * 0.05F;
				transform.scale = math::ONE * 30.f;
				auto& renderer = this->registry_.emplace<MeshRenderer>(cube);
				auto& collider = this->registry_.emplace<Collider>(cube);

				meta.name = "Solider " + std::to_string(i + j);
				Material::BumpedDiffuse lambert;
				lambert.albedo = _resource_manager.load<Texture>("examples/soldier_albedo.dds");
				TextureMeta tmeta = {};
				tmeta.is_srgb = false;
				lambert.normal = _resource_manager.load<Texture>("examples/soldier_normal.dds", &tmeta);
				renderer.material = Material::create_from_data(lambert, "soldier", _resource_manager);
				renderer.mesh = _resource_manager.load<Mesh>("examples/soldier.obj");
			}
		}

		// Load skybox:
		this->config.lighting.skybox_cubemap = _resource_manager.system_resources.skybox;
		this->config.lighting.skydome = _resource_manager.system_resources.skydome;
	}

	void Scenery::unload_all_entities() {
		this->registry_.clear();
	}
} // namespace dce
