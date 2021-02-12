#pragma once

#include "../../extern/json/include/nlohmann/json_fwd.hpp"
#include <filesystem>

namespace PowerRonin
{
	using JsonStream = nlohmann::basic_json<>;

	/// <summary>
	/// Base interface for all serializable objects.
	/// </summary>
	class ISerializable
	{
	public:
		ISerializable() noexcept = default;
		ISerializable(const ISerializable&) noexcept = default;
		ISerializable(ISerializable&&) noexcept = default;
		auto operator=(const ISerializable&) noexcept -> ISerializable& = default;
		auto operator=(ISerializable&&) noexcept -> ISerializable& = default;
		virtual ~ISerializable() = default;

		virtual void serialize(JsonStream&) const = 0;

		virtual void deserialize(const JsonStream&) = 0;

		[[nodiscard]] virtual auto serialize_to_file(const std::filesystem::path& _path) const -> bool;

		virtual auto deserialize_from_file(const std::filesystem::path& _path) -> bool;
	};
} // namespace PowerRonin // namespace PowerRonin
