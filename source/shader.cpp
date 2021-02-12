#include "../Include/PowerRonin/Shader.hpp"

namespace PowerRonin
{
	auto Shader::vertex_shader_bytecode() const noexcept -> const Blob&
	{
		return this->vertex_shader_bytecode_;
	}

	auto Shader::fragment_shader_bytecode() const noexcept -> const std::optional<Blob>&
	{
		return this->fragment_shader_bytecode_;
	}

	auto Shader::vertex_shader_textcode() const noexcept -> const std::optional<std::string>&
	{
		return this->vertex_shader_textcode_;
	}

	auto Shader::fragment_shader_textcode() const noexcept -> const std::optional<std::string>&
	{
		return this->fragment_shader_textcode_;
	}

	auto Shader::program_id() const noexcept -> std::uint16_t
	{
		return this->volatile_upload_data_.program_id;
	}
}
