// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: resource.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 05.11.2020 20:09

#pragma once

#include "ecs.hpp"
#include <filesystem>

namespace dce {
	class IResource;

	template <typename Importeur, typename Resource> requires std::is_base_of_v<IResource, Resource> using ResourceImporteur =
	entt::resource_loader<Importeur, Resource>;

	template <typename Resource> requires std::is_base_of_v<IResource, Resource>using ResourceCache = entt::resource_cache<
		Resource>;

	template <typename Resource> requires std::is_base_of_v<IResource, Resource>using ResourceHandle = entt::resource_handle<
		Resource>;

	class IResource {
	public:

		IResource(const IResource &) = delete;
		IResource(IResource &&) = delete;
		auto operator=(const IResource &) -> IResource& = delete;
		auto operator=(IResource &&) noexcept -> IResource& = default;
		virtual ~IResource() = default;

		/* Upload resource to target system. */
		virtual void upload() = 0;

		/* Offload resource from target system. */
		virtual void offload() = 0;

		[[nodiscard]] auto get_file_path() const noexcept -> const std::filesystem::path&;

		[[nodiscard]] auto is_uploaded() const noexcept -> bool;

		template <typename T, typename... Q> requires std::is_base_of_v<IResource, T> [[nodiscard]] static auto allocate(
			Q &&..._args) -> std::shared_ptr<T>;

	protected:
		IResource() = default;
		std::filesystem::path file_path_ = {};
		bool uploaded_ = false;
	};

	template <typename T, typename ... Q> requires std::is_base_of_v<IResource, T>inline auto IResource::allocate(
		Q &&... _args) -> std::shared_ptr<T> {
		return std::shared_ptr<T>(new T(_args...), [](T *const _ptr) {
			if (_ptr) {
				_ptr->offload();
				delete _ptr;
			}
		});
	}
} // namespace dce // namespace dce
