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

#include <string>
#include <cstdint>

namespace power_ronin
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
