// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: ecs.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "../../extern/entt/single_include/entt/entt.hpp"

namespace dce {
	using ID = entt::id_type;

	using HString = entt::hashed_string;

	using Registry = entt::registry;

	using ERef = entt::entity;
} // namespace dce
