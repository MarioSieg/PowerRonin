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
