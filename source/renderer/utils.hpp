#pragma once

#include <cstdint>

namespace power_ronin::renderer
{
	extern auto check_available_transient_buffers(std::uint32_t vertex_count
	                                              , std::uint32_t index_count
	                                              , const void* layout) -> bool;
} // namespace power_ronin::renderer
