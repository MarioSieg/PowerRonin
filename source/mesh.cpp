#include "../include/dce/mesh.hpp"


namespace dce {
	auto Mesh::get_indices() const noexcept -> const std::vector<std::uint16_t>& {
		return this->indices_;
	}

	auto Mesh::get_index_buffer_id() const noexcept -> std::uint16_t {
		return this->volatile_upload_data_.index_buffer_id;
	}

	auto Mesh::get_vertices() const noexcept -> const std::vector<Vertex>& {
		return this->vertices_;
	}

	auto Mesh::get_vertex_buffer_id() const noexcept -> std::uint16_t {
		return this->volatile_upload_data_.vertex_buffer_id;
	}
} // namespace dce // namespace dce
