// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: shader.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 11.11.2020 21:45

#include "../include/dce/shader.hpp"

namespace dce {

	auto Shader::get_vertex_shader_bytecode() const noexcept -> const std::vector<std::byte>& {
		return this->vertex_shader_bytecode_;
	}

	auto Shader::get_fragment_shader_bytecode() const noexcept -> const std::vector<std::byte>& {
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

	auto Shader::get_sampler_id() const noexcept -> std::uint16_t {
		return this->volatile_upload_data_.sampler_uniform_id;
	}

}
