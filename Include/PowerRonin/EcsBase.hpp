#pragma once

#include "../../extern/entt/single_include/entt/entt.hpp"
#include <type_traits>

namespace PowerRonin
{
	using EntityID = entt::id_type;

	using HashedString = entt::hashed_string;

	using Registry = entt::registry;

	using EntityRef = entt::entity;

	template <typename T>
	class IResource;

	template <typename Importeur, typename Resource> requires std::is_base_of_v<IResource<typename Resource::Meta>, Resource> using
	ResourceImporteur = entt::resource_loader<Importeur, Resource>;

	template <typename Resource> requires std::is_base_of_v<IResource<typename Resource::Meta>, Resource> using
	ResourceCache = entt::resource_cache<Resource>;

	template <typename Resource> requires std::is_base_of_v<IResource<typename Resource::Meta>, Resource> using RRef =
	entt::resource_handle<Resource>;

	template <typename Resource>
	using ResourceRef = entt::resource_handle<Resource>;
} // namespace PowerRonin
