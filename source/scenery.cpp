// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

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

	void Scenery::new_default(ResourceManager& _resource_manager) {
		// Create cube:
		{
			const auto cube = this->registry_.create();

			auto& meta = this->registry_.emplace<MetaData>(cube);
			auto& transform = this->registry_.emplace<Transform>(cube);
			auto& audio = this->registry_.emplace<AudioSource>(cube);
			auto& renderer = this->registry_.emplace<MeshRenderer>(cube);
			auto& collider = this->registry_.emplace<Collider>(cube);

			meta.name = "Cube";
			Material::Lambert lambert;
			Material::get_default_properties(lambert, _resource_manager);
			renderer.material = Material::create_from_data(lambert, "cube", _resource_manager);
			renderer.mesh = _resource_manager.system_resources.cube;
			AudioClipMeta aumeta = {};
			aumeta.enable_3d_sound = false;
			aumeta.is_stream = true;
			audio.clip = _resource_manager.load<AudioClip>("audio/music/entry.ogg", &aumeta);
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
			Material::Lambert lambert;
			Material::get_default_properties(lambert, _resource_manager);
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
