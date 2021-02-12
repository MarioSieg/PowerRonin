#include "../Include/PowerRonin/Mesh.hpp"

namespace PowerRonin
{
	auto Mesh::Indices() const noexcept -> const std::vector<std::uint16_t>&
	{
		return this->indices;
	}

	auto Mesh::IndexBufferId() const noexcept -> std::uint16_t
	{
		return this->volatileUploadData.IndexBufferId;
	}

	auto Mesh::Vertices() const noexcept -> const std::vector<Vertex>&
	{
		return this->vertices;
	}

	auto Mesh::VertexBufferId() const noexcept -> std::uint16_t
	{
		return this->volatileUploadData.VertexBufferId;
	}

	auto Mesh::Aabb() const noexcept -> const struct Aabb&
	{
		return this->aabb;
	}
} // namespace PowerRonin // namespace PowerRonin
