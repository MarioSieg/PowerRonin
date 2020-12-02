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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../include/dce/shader.hpp"

namespace dce {
	auto Shader::get_vertex_shader_bytecode() const noexcept -> const std::vector<std::byte>& {
		return this->vertex_shader_bytecode_;
	}

	auto Shader::get_fragment_shader_bytecode() const noexcept -> const std::optional<std::vector<std::byte>>& {
		return this->fragment_shader_bytecode_;
	}

	auto Shader::get_vertex_shader_textcode() const noexcept -> const std::optional<std::string>& {
		return this->vertex_shader_textcode_;
	}

	auto Shader::get_fragment_shader_textcode() const noexcept -> const std::optional<std::string>& {
		return this->fragment_shader_textcode_;
	}

	auto Shader::get_program_id() const noexcept -> std::uint16_t {
		return this->volatile_upload_data_.program_id;
	}

	auto Shader::get_uniforms() const noexcept -> const std::unordered_map<std::string_view, std::tuple<UniformType, std::uint16_t>>& {
		return this->volatile_upload_data_.uniforms;
	}
}
