#pragma once

#include <filesystem>
#include <string_view>

#include "EcsBase.hpp"
#include "Serial.hpp"
#include "Exceptions.hpp"

namespace PowerRonin
{
	/// <summary>
	/// Base class for all runtime resources.
	/// </summary>
	/// <typeparam name="M">Metadata type.</typeparam>
	template <typename M>
	class IResource
	{
		static_assert(std::is_move_assignable_v<M>);
		static_assert(std::is_base_of_v<ISerializable, M>);
		static_assert(std::is_default_constructible_v<M>);
		
	public:
		using Meta = M;

		static constexpr std::string_view MetaDataFileExtension = ".meta";

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
		[[nodiscard]] auto FilePath() const noexcept -> const std::filesystem::path&
		{
			return this->filePath;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns>True if the resource is currently uploaded, else false..</returns>
		[[nodiscard]] auto IsUploaded() const noexcept -> bool
		{
			return this->isUploaded;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The metadata of the resource.</returns>
		[[nodiscard]] auto MetaData() const noexcept -> const Meta&
		{
			return this->metaData;
		}

		/// <summary>
		/// Allocate resource memory.
		/// </summary>
		/// <typeparam name="T">The type of resource.</typeparam>
		/// <typeparam name="...Q">The constructor arguments.</typeparam>
		/// <param name="args">The constructor arguments.</param>
		/// <returns>The shared_ptr with the allocated resource.</returns>
		template <typename T, typename... Q> requires std::is_base_of_v<IResource<M>, T> && std::is_constructible_v<T, Q...>
		[[nodiscard]]
		inline static auto Allocate(Q&&... args) -> std::shared_ptr<T>
		{
			auto* const mem = new(std::nothrow) T(args...);
			if (!mem) [[unlikely]] throw MAKE_FATAL_ENGINE_EXCEPTION("bad allocation");
			return std::shared_ptr<T>(mem, [](T*& ptr) mutable
			{
				if (ptr) [[likely]] ptr->Offload();
				delete ptr, ptr = nullptr;
			});
		}

		/// <summary>
		/// Tries to load some resource metadata from a .meta file.
		/// If it fails, it tries to Create the meta file and returns
		/// the default value of Meta.
		/// </summary>
		/// <param name="path">The resource file path..</param>
		/// <returns>The deserialized metadata or the default value.</returns>
		[[nodiscard]] static inline auto LoadMetaOrDefault(std::filesystem::path path) -> Meta
		{
			path.replace_extension(MetaDataFileExtension);
			Meta meta = {};
			auto* const ser = &meta;
			if (!ser->deserialize_from_file(path)) [[unlikely]]
			{
				//auto _ = ser->serialize_to_file(_res); // Create metadata file if it does not exist.
			}
			return meta;
		}

	protected:
		IResource() = default;
		explicit IResource(Meta&& meta) noexcept : metaData(meta) { }

		std::filesystem::path filePath = {};
		bool isUploaded = false;
		Meta metaData = {};
	};
} // namespace PowerRonin // namespace PowerRonin
