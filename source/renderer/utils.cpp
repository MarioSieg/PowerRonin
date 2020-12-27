#include "utils.hpp"
#include "gl_headers.hpp"

namespace dce::renderer {
	auto check_available_transient_buffers(const std::uint32_t vertex_count
	                                       , const std::uint32_t index_count
	                                       , const void* const layout) -> bool {
		return vertex_count == getAvailTransientVertexBuffer(vertex_count,
		                                                     *static_cast<const bgfx::VertexLayout* const>(layout)) &&
			(0 == index_count || index_count == bgfx::getAvailTransientIndexBuffer(index_count));
	}
} // namespace dce::renderer
