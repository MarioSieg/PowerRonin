#pragma once

#include <cstdint>

namespace dce::renderer
{
	extern auto check_available_transient_buffers(std::uint32_t vertex_count
	                                              , std::uint32_t index_count
	                                              , const void* layout) -> bool;
} // namespace dce::renderer
