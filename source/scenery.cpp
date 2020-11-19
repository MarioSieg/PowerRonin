// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: scenery.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "../include/dce/scenery.hpp"
#include "../include/dce/resource_manager.hpp"

namespace dce {

	auto Scenery::registry() const noexcept -> const Registry& {
		return this->registry_;
	}

	auto Scenery::registry() noexcept -> Registry& {
		return this->registry_;
	}

	void Scenery::initialize() { }

	void Scenery::new_default(ResourceManager &_resource_manager) {
		{
			const auto cube = this->registry_.create();

			auto &meta = this->registry_.emplace<MetaData>(cube);
			[[maybe_unused]] auto &transform = this->registry_.emplace<Transform>(cube);
			auto &renderer = this->registry_.emplace<MeshRenderer>(cube);
			[[maybe_unused]] auto &collider = this->registry_.emplace<Collider>(cube);
			[[maybe_unused]] auto &rigidbody = this->registry_.emplace<Rigidbody>(cube);

			meta.name = "Cube";

			renderer.texture = _resource_manager.system_resources.textures.error_marker;
			renderer.mesh = _resource_manager.mesh_cache.load<MeshImporteur>(
				_resource_manager.gen_id(), "meshes/common/cube.obj");
			renderer.shader = _resource_manager.system_resources.shaders.unlit;
		}
		{
			const auto platform = this->registry_.create();

			auto &meta = this->registry_.emplace<MetaData>(platform);
			auto &transform = this->registry_.emplace<Transform>(platform);
			auto &renderer = this->registry_.emplace<MeshRenderer>(platform);

			meta.name = "Platform";
			transform.position.y = -1.f;
			transform.scale *= 3.f;

			renderer.texture = _resource_manager.system_resources.textures.error_marker;
			renderer.mesh = _resource_manager.mesh_cache.load<MeshImporteur>(
				_resource_manager.gen_id(), "meshes/common/platform.obj");
			renderer.shader = _resource_manager.system_resources.shaders.unlit;
		}
		{
			const auto sun = this->registry_.create();

			auto &transform = this->registry_.emplace<Transform>(sun);
			auto &light = this->registry_.emplace<Light>(sun);
		}
	}
} // namespace dce
