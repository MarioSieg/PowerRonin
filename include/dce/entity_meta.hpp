#pragma once

#include <string>
#include <cstdint>

namespace dce
{
	/* Base metadata component for entities. */
	class MetaData final
	{
	public:
		MetaData() noexcept = default;
		MetaData(const MetaData&) = delete;
		MetaData(MetaData&&) noexcept = default;
		auto operator=(const MetaData&) -> MetaData& = delete;
		auto operator=(MetaData&&) noexcept -> MetaData& = default;
		~MetaData() = default;

		std::string name = {};
		std::string description = {};
		void* user_data = nullptr;
		std::uint16_t tag = 0;
		std::uint16_t layer = 0;
	};
}
