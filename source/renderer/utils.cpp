// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: utils.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#include "utils.hpp"
#include "bgfx_headers.hpp"

namespace dce::renderer {
	auto check_available_transient_buffers(const std::uint32_t vertex_count, const std::uint32_t index_count
	                                       , const void *const layout) -> bool {
		return vertex_count == getAvailTransientVertexBuffer(
			vertex_count, *static_cast<const bgfx::VertexLayout * const>(layout)) && (0 == index_count || index_count ==
			bgfx::getAvailTransientIndexBuffer(index_count));
	}
} // namespace dce::renderer
