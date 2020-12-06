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

#pragma once

#include "ecs.hpp"
#include "comcollections.hpp"

namespace dce {
	class ResourceManager;

	/// <summary>
	/// Types of Skyboxes.
	/// </summary>
	enum class SkyboxType {
		/// <summary>
		/// Dynamic skybox (based on scenery daytime, weather)
		/// </summary>
		DYNAMIC,

		/// <summary>
		/// Static skybox (cubemap image).
		/// </summary>
		STATIC
	};

	/// <summary>
	/// Represents a scenery environment.
	/// </summary>
	class Scenery final {
		friend class Runtime;
	public:
		/// <summary>
		/// Contains per scenery settings.
		/// </summary>
		struct Configuration final {
			struct Lighting final {
				struct {
					/// <summary>
					/// The sun latitude.
					/// </summary>
					float latitude = 50.f;

					/// <summary>
					/// The sun hour. (Only if "sync_hour_with_env_time" == false)
					/// </summary>
					float hour = 0.f;

					/// <summary>
					/// If true, the scenery time will be used as sun hour too.
					/// </summary>
					bool sync_hour_with_env_time = false;

					/// <summary>
					/// The color of the sunlight.
					/// </summary>
					Color<> color = math::rgba_to_rgba_norm(0xFFFFFFFF);
				} sun;

				/// <summary>
				/// Basic constant ambient color.
				/// </summary>
				Color<> const_ambient_color = math::rgba_to_rgba_norm(0xAAAAAAAA);

				/// <summary>
				/// The type of the scenery skybox.
				/// </summary>
				SkyboxType skybox_type = SkyboxType::STATIC;

				/// <summary>
				/// The cubemap texture of the skybox (only used if "skybox_type" == SkyboxType::STATIC)!
				/// </summary>
				RRef<Texture> skybox_cubemap;

				/// <summary>
				/// The skydome cube or sphere mesh on which the skybox cubemap will be rendered on.
				/// </summary>
				RRef<Mesh> skydome;
			} lighting;
		};

		Scenery() = default;
		Scenery(const Scenery&) = delete;
		Scenery(Scenery&&) = delete;
		auto operator=(const Scenery&) -> Scenery& = delete;
		auto operator=(Scenery&&) -> Scenery& = delete;
		~Scenery() = default;

		std::string name = {};
		std::string description = {};
		Configuration config = {};

		[[nodiscard]] auto registry() const noexcept -> const Registry&;

		[[nodiscard]] auto registry() noexcept -> Registry&;

		void unload_all_entities();

	private:
		Registry registry_ = {};
		void initialize();
		void new_default(ResourceManager& _resource_manager);
	};
} // namespace dce // namespace dce
