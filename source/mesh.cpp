#include "../include/power_ronin/mesh.hpp"

namespace power_ronin
{
	auto Mesh::indices() const noexcept -> const std::vector<std::uint16_t>&
	{
		return this->indices_;
	}

	auto Mesh::index_buffer_id() const noexcept -> std::uint16_t
	{
		return this->volatile_upload_data_.index_buffer_id;
	}

	auto Mesh::vertices() const noexcept -> const std::vector<Vertex>&
	{
		return this->vertices_;
	}

	auto Mesh::vertex_buffer_id() const noexcept -> std::uint16_t
	{
		return this->volatile_upload_data_.vertex_buffer_id;
	}

	auto Mesh::aabb() const noexcept -> const AABB&
	{
		return this->aabb_;
	}
} // namespace power_ronin // namespace power_ronin
