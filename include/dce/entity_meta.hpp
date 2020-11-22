// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: entity_meta.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 16.11.2020 11:47

#pragma once

#include <string>

namespace dce {
	/* Base metadata component for entities. */
	class MetaData final {
	public:
		std::string name = {};
		std::string description = {};
		void* user_data = nullptr;
		std::uint16_t tag = 0;
		std::uint16_t layer = 0;
	};
}
