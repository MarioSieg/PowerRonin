#pragma once

#include "ecs.hpp"
#include "serial.hpp"
#include <filesystem>

#include "except.hpp"

namespace power_ronin
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
		virtual void upload() = 0;

		/// <summary>
		/// Upload resource from target subsystem.
		/// For example: delete texture from VRAM, but keep it in RAM to upload() it again if needed.
		/// </summary>
		virtual void offload() = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The file path of the resource.</returns>
		[[nodiscard]] auto file_path() const noexcept -> const std::filesystem::path&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>True if the resource is currently uploaded, else false..</returns>
		[[nodiscard]] auto is_uploaded() const noexcept -> bool;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The metadata of the resource.</returns>
		[[nodiscard]] auto meta_data() const noexcept -> const Meta&;

		/// <summary>
		/// Allocate resource memory.
		/// </summary>
		/// <typeparam name="T">The type of resource.</typeparam>
		/// <typeparam name="...Q">The constructor arguments.</typeparam>
		/// <param name="_x">The constructor arguments.</param>
		/// <returns>The shared_ptr with the allocated resource.</returns>
		template <typename T, typename... Q> requires requires
		{
			requires std::is_base_of_v<IResource<M>, T>; requires std::is_constructible_v<T, Q...>;
		} [[nodiscard]] inline static auto allocate(Q&&... _x) -> std::shared_ptr<T>
		{
			auto* const mem = new(std::nothrow) T(_x...);
			if (!mem) [[unlikely]] throw MAKE_FATAL_ENGINE_EXCEPTION("Bad allocation!");
			return std::shared_ptr<T>(mem, [](T*& _y) mutable
			{
				if (_y) [[likely]] _y->offload();
				delete _y, _y = nullptr;
			});
		}

		/// <summary>
		/// Tries to load some resource metadata from a .meta file.
		/// If it fails, it tries to create the meta file and returns
		/// the default value of Meta.
		/// </summary>
		/// <param name="_res">The resource file path..</param>
		/// <returns>The deserialized metadata or the default value.</returns>
		[[nodiscard]] static auto load_meta_or_default(std::filesystem::path _res) -> Meta;

	protected:
		IResource() = default;
		explicit IResource(Meta&& _meta) noexcept;
		std::filesystem::path file_path_ = {};
		bool is_uploaded_ = false;
		Meta meta_data_ = {};
	};

	template <typename M>
	inline auto IResource<M>::is_uploaded() const noexcept -> bool
	{
		return this->is_uploaded_;
	}

	template <typename M>
	inline auto IResource<M>::meta_data() const noexcept -> const Meta&
	{
		return this->meta_data_;
	}

	template <typename M>
	inline auto IResource<M>::file_path() const noexcept -> const std::filesystem::path&
	{
		return this->file_path_;
	}

	template <typename M>
	inline auto IResource<M>::load_meta_or_default(std::filesystem::path _res) -> Meta try
	{
		_res.replace_extension(METADATA_FILE_EXTENSION);
		Meta meta = {};
		auto* const ser = &meta;
		if (!ser->deserialize_from_file(_res)) [[unlikely]]
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
	inline IResource<M>::IResource(Meta&& _meta) noexcept : meta_data_(std::forward(_meta)) { }
} // namespace power_ronin // namespace power_ronin
