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
