// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: json_impl.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "../../extern/json/single_include/nlohmann/json.hpp"

namespace dce {
	using JsonStream = nlohmann::basic_json<>;
} // namespace dce
