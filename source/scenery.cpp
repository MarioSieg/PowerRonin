// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: scenery.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 08.11.2020 19:28

#include "../include/dce/scenery.hpp"
#include "../include/dce/resource_manager.hpp"
#include "../include/dce/mesh_renderer.hpp"
#include "../include/dce/transform.hpp"

namespace dce {

	auto Scenery::registry() const noexcept -> const Registry& {
		return this->registry_;
	}

	auto Scenery::registry() noexcept -> Registry& {
		return this->registry_;
	}

	void Scenery::initialize() { }

	void Scenery::new_default(const ResourceManager &_resource_manager) {
		for (auto i = 0; i < 10; ++i) {
			for (auto j = 0; j < 10; ++j) {
				const auto cube = this->registry_.create();

				auto &transform = this->registry_.emplace<Transform>(cube);
				auto &renderer = this->registry_.emplace<MeshRenderer>(cube);

				transform.position.x = i * 4.f;
				transform.position.z = j * 4.f;
				renderer.texture = _resource_manager.system_resources.checkerboard_texture;
				renderer.mesh = _resource_manager.system_resources.cube_mesh;
				renderer.shader = _resource_manager.system_resources.basic_shader;
			}
		}
	}
} // namespace dce
