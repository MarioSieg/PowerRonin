// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: ecs.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 08.11.2020 19:14

#pragma once

#include "../../extern/entt/single_include/entt/entt.hpp"

namespace dce {
	using ID = entt::id_type;

	using HString = entt::hashed_string;

	using Registry = entt::registry;

	using EntityHandle = entt::entity;
} // namespace dce
