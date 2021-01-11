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

#include "../include/power_ronin/scenery.hpp"
#include "../include/power_ronin/resource_manager.hpp"

namespace power_ronin
{
	auto Scenery::registry() const noexcept -> const Registry&
	{
		return this->registry_;
	}

	auto Scenery::registry() noexcept -> Registry&
	{
		return this->registry_;
	}

	void Scenery::initialize() { }

	void Scenery::new_default(ResourceManager& _resource_manager)
	{
		// Camera:
		const auto camera_entity = this->registry_.create();
		auto& transform = this->registry_.emplace<Transform>(camera_entity);
		transform.position = {.5f, .0f, -10.f};
		auto& camera = this->registry_.emplace<Camera>(camera_entity);

		// Create cube:
		for (auto i = 0, z = 1; i < 8; ++i)
		{
			for (auto j = 0; j < 8; ++j, ++z)
			{
				const auto cube = this->registry_.create();

				auto& meta = this->registry_.emplace<MetaData>(cube);
				auto& transform = this->registry_.emplace<Transform>(cube);
				transform.position.x = i * 5.F;
				transform.position.z = j * 5.F;
				auto& renderer = this->registry_.emplace<MeshRenderer>(cube);
				auto& collider = this->registry_.emplace<Collider>(cube);

				meta.name = "Solider " + std::to_string(z);
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
		this->config.lighting.skybox_material = Material::create_from_data(
			Material::StaticSkybox{_resource_manager.system_resources.skybox}, "_skybox_", _resource_manager);
		this->config.lighting.skydome = _resource_manager.system_resources.skydome;
	}

	void Scenery::unload_all_entities()
	{
		this->registry_.clear();
	}
} // namespace power_ronin
