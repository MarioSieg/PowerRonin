#include "../include/dce/shader.hpp"

namespace dce {
	auto Shader::get_vertex_shader_bytecode() const noexcept -> const Blob& {
		return this->vertex_shader_bytecode_;
	}

	auto Shader::get_fragment_shader_bytecode() const noexcept -> const std::optional<Blob>& {
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

	auto Shader::get_uniforms() const noexcept -> const std::unordered_map<
		std::string_view, std::tuple<UniformType, std::uint16_t>>& {
		return this->volatile_upload_data_.uniforms;
	}
}
