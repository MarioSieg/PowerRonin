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

#pragma once

#include "ecs.hpp"
#include "serial.hpp"
#include <filesystem>

#include "except.hpp"

namespace PowerRonin
{
	/// <summary>
	/// Base class for all runtime resources.
	/// </summary>
	/// <typeparam name="M">Metadata type.</typeparam>
	template <typename M>
	class IResource
	{
		static_assert(std::is_move_assignable_v<M>, "Resource metadata must be at least move assignable!");
		static_assert(std::is_base_of_v<ISerializable, M>, "Resource metadata must be serializable!");
		static_assert(std::is_default_constructible_v<M>, "Resource metadata must be default constructible!");

	public:
		using Meta = M;

		static constexpr std::string_view METADATA_FILE_EXTENSION = ".meta";

		IResource(const IResource&) = delete;
		IResource(IResource&&) = delete;
		auto operator=(const IResource&) -> IResource& = delete;
		auto operator=(IResource&&) noexcept -> IResource& = default;
		virtual ~IResource() = default;

		/// <summary>
		/// Upload resource to target subsystem.
		/// For example: upload texture from RAM to VRAM.
		/// </summary>
		virtual void Upload() = 0;

		/// <summary>
		/// Upload resource from target subsystem.
		/// For example: delete texture from VRAM, but keep it in RAM to upload() it again if needed.
		/// </summary>
		virtual void Offload() = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The file path of the resource.</returns>
		[[nodiscard]] auto FilePath() const noexcept -> const std::filesystem::path&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>True if the resource is currently uploaded, else false..</returns>
		[[nodiscard]] auto IsUploaded() const noexcept -> bool;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The metadata of the resource.</returns>
		[[nodiscard]] auto MetaData() const noexcept -> const Meta&;

		/// <summary>
		/// Allocate resource memory.
		/// </summary>
		/// <typeparam name="T">The type of resource.</typeparam>
		/// <typeparam name="...Q">The constructor arguments.</typeparam>
		/// <param name="_x">The constructor arguments.</param>
		/// <returns>The shared_ptr with the allocated resource.</returns>
		template <typename T, typename... Q> requires std::is_base_of_v<IResource<M>, T> && std::is_constructible_v<T, Q...>
		[[nodiscard]]
		inline static auto Allocate(Q&&... args) -> std::shared_ptr<T>
		{
			auto* const mem = new(std::nothrow) T(args...);
			if (!mem) [[unlikely]] throw MAKE_FATAL_ENGINE_EXCEPTION("Bad allocation!");
			return std::shared_ptr<T>(mem, [](T*& _y) mutable
			{
				if (_y) [[likely]] _y->Offload();
				delete _y, _y = nullptr;
			});
		}

		/// <summary>
		/// Tries to load some resource metadata from a .meta file.
		/// If it fails, it tries to Create the meta file and returns
		/// the default value of Meta.
		/// </summary>
		/// <param name="path">The resource file path..</param>
		/// <returns>The deserialized metadata or the default value.</returns>
		[[nodiscard]] static auto LoadMetaOrDefault(std::filesystem::path path) -> Meta;

	protected:
		IResource() = default;
		explicit IResource(Meta&& meta) noexcept;
		std::filesystem::path filePath = {};
		bool isUploaded = false;
		Meta metaData = {};
	};

	template <typename M>
	inline auto IResource<M>::IsUploaded() const noexcept -> bool
	{
		return this->isUploaded;
	}

	template <typename M>
	inline auto IResource<M>::MetaData() const noexcept -> const Meta&
	{
		return this->metaData;
	}

	template <typename M>
	inline auto IResource<M>::FilePath() const noexcept -> const std::filesystem::path&
	{
		return this->filePath;
	}

	template <typename M>
	inline auto IResource<M>::LoadMetaOrDefault(std::filesystem::path path) -> Meta try
	{
		path.replace_extension(METADATA_FILE_EXTENSION);
		Meta meta = {};
		auto* const ser = &meta;
		if (!ser->deserialize_from_file(path)) [[unlikely]]
		{
			//auto _ = ser->serialize_to_file(_res); // Create metadata file if it does not exist.
		}
		return meta;
	}
	catch (...)
	{
		return {};
	}

	template <typename M>
	inline IResource<M>::IResource(Meta&& meta) noexcept : metaData(std::forward(meta)) { }
} // namespace PowerRonin // namespace PowerRonin
