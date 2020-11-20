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

	class Scenery final {
		friend class State;
	public:
		Scenery() = default;
		Scenery(const Scenery &) = delete;
		Scenery(Scenery &&) = delete;
		auto operator=(const Scenery &) -> Scenery& = delete;
		auto operator=(Scenery &&) -> Scenery& = delete;
		~Scenery() = default;

		std::string name = {};
		std::string description = {};

		struct {
			float latitude = .0f;
			float hour = 12.f;
		} sun = {};

		[[nodiscard]] auto registry() const noexcept -> const Registry&;

		[[nodiscard]] auto registry() noexcept -> Registry&;

	private:
		Registry registry_ = {};
		void initialize();
		void new_default(ResourceManager &_resource_manager);
	};
} // namespace dce // namespace dce
