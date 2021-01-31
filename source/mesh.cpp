// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#include "../include/power_ronin/mesh.hpp"

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
