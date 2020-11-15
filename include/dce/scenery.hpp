// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: scenery.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 08.11.2020 19:24

#pragma once

#include "ecs.hpp"

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

		[[nodiscard]] auto registry() const noexcept -> const Registry&;

		[[nodiscard]] auto registry() noexcept -> Registry&;

	private:
		Registry registry_ = {};
		void initialize();
		void new_default(const ResourceManager &_resource_manager);
	};
} // namespace dce // namespace dce
