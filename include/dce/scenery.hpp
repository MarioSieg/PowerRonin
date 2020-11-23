// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: scenery.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "ecs.hpp"
#include "comcollections.hpp"

namespace dce {
	class ResourceManager;

	/// <summary>
	/// Represents a scenery environment.
	/// </summary>
	class Scenery final {
		friend class State;
	public:
		/// <summary>
		/// Contains per scenery settings.
		/// </summary>
		struct Configuration final {
			struct {
				struct {
					float latitude = 50.f;
					float hour = 12.f;
					bool sync_hour_with_env_time = false;
					Color<> color = math::rgba_to_rgba_norm(0xFFFFFFFF);
				} sun;

				Color<> const_ambient_color = math::rgba_to_rgba_norm(0xFFFFFFFF);
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

	private:
		Registry registry_ = {};
		void initialize();
		void new_default(ResourceManager& _resource_manager);
	};
} // namespace dce // namespace dce
