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

	void Scenery::new_default(const ResourceManager &_resource_manager) {
		const auto cube = this->registry_.create();

		auto &meta = this->registry_.emplace<CMetaData>(cube);
		auto &transform = this->registry_.emplace<CTransform>(cube);
		auto &renderer = this->registry_.emplace<CMeshRenderer>(cube);

		meta.name = "Bunny";

		renderer.texture = _resource_manager.system_resources.checkerboard_texture;
		renderer.mesh = _resource_manager.system_resources.cube_mesh;
		renderer.shader = _resource_manager.system_resources.basic_shader;
	}
} // namespace dce
