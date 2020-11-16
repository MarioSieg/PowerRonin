// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: utils.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include <cstdint>

namespace dce::renderer {
	extern auto check_available_transient_buffers(std::uint32_t vertex_count, std::uint32_t index_count
	                                              , const void *layout) -> bool;
} // namespace dce::renderer
