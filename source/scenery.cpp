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

			auto &meta = this->registry_.emplace<CMetaData>(cube);
			[[maybe_unused]] auto &transform = this->registry_.emplace<Transform>(cube);
			auto &renderer = this->registry_.emplace<CMeshRenderer>(cube);
			[[maybe_unused]] auto &collider = this->registry_.emplace<Collider>(cube);
			[[maybe_unused]] auto &rigidbody = this->registry_.emplace<Rigidbody>(cube);

			meta.name = "Cube";

			renderer.texture = _resource_manager.system_resources.checkerboard_texture;
			renderer.mesh = _resource_manager.mesh_cache.load<MeshImporteur>(
				_resource_manager.gen_id(), "meshes/common/cube.obj");
			renderer.shader = _resource_manager.system_resources.basic_shader;
		}
		{
			const auto platform = this->registry_.create();

			auto &meta = this->registry_.emplace<CMetaData>(platform);
			auto &transform = this->registry_.emplace<Transform>(platform);
			auto &renderer = this->registry_.emplace<CMeshRenderer>(platform);

			meta.name = "Platform";
			transform.position.y = -1.f;
			transform.scale *= 3.f;

			renderer.texture = _resource_manager.system_resources.checkerboard_texture;
			renderer.mesh = _resource_manager.mesh_cache.load<MeshImporteur>(
				_resource_manager.gen_id(), "meshes/common/platform.obj");
			renderer.shader = _resource_manager.system_resources.basic_shader;
		}

	}
} // namespace dce
