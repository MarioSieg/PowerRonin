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
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

#include "../../extern/entt/single_include/entt/entt.hpp"
#include <type_traits>

namespace dce {
	using ID = entt::id_type;

	using HString = entt::hashed_string;

	using Registry = entt::registry;

	using ERef = entt::entity;

	template <typename T>
	class IResource;

	template <typename Importeur, typename Resource> requires std::is_base_of_v<IResource<typename Resource::Meta>, Resource> using
	ResourceImporteur = entt::resource_loader<Importeur, Resource>;

	template <typename Resource> requires std::is_base_of_v<IResource<typename Resource::Meta>, Resource> using ResourceCache =
	entt::resource_cache<Resource>;

	template <typename Resource> requires std::is_base_of_v<IResource<typename Resource::Meta>, Resource> using RRef =
	entt::resource_handle<Resource>;

	template <typename Resource>
	using IRef = entt::resource_handle<Resource>;

	using HString = entt::hashed_string;
} // namespace dce
