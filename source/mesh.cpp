// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

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
