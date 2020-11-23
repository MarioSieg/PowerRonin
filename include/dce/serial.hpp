// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: serial.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "../../extern/json/include/nlohmann/json_fwd.hpp"
#include <filesystem>

namespace dce {
	using JsonStream = nlohmann::basic_json<>;

	class ISerializable {
	public:
		ISerializable() noexcept = default;
		ISerializable(const ISerializable&) noexcept = default;
		ISerializable(ISerializable&&) noexcept = default;
		auto operator=(const ISerializable&) noexcept -> ISerializable& = default;
		auto operator=(ISerializable&&) noexcept -> ISerializable& = default;
		virtual ~ISerializable() = default;


		virtual auto serialize(JsonStream&) const -> bool = 0;
		virtual auto deserialize(const JsonStream&) -> bool = 0;
		[[nodiscard]] virtual auto serialize_to_file(const std::filesystem::path& /*path*/) const -> bool;
		virtual auto deserialize_from_file(const std::filesystem::path& /*path*/) -> bool;
	};
} // namespace dce // namespace dce
