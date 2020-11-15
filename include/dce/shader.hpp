// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: shader.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 11.11.2020 21:27

#pragma once

#include "resource.hpp"
#include <optional>

namespace dce {
	/* Represents a shader program with vertex and fragmet shader. */
	class Shader final : public IResource {
		friend class ShaderImporteur;
		friend class ShaderCompiler;

	public:
		/* All associated file types. */
		static constexpr std::array<std::string_view, 4> FILE_EXTENSIONS = {
			".fxc", ".vshader", /* vertex shader */
			".fshader"
			, /* fragment shader */
			".hshader"
			, /* shader header */
		};

		[[nodiscard]] auto get_vertex_shader_bytecode() const noexcept -> const std::vector<std::byte>&;

		[[nodiscard]] auto get_fragment_shader_bytecode() const noexcept -> const std::vector<std::byte>&;

		[[nodiscard]] auto get_vertex_shader_textcode() const noexcept -> const std::optional<std::string>&;

		[[nodiscard]] auto get_fragment_shader_textcode() const noexcept -> const std::optional<std::string>&;

		[[nodiscard]] auto get_program_id() const noexcept -> std::uint16_t;

		[[nodiscard]] auto get_sampler_id() const noexcept -> std::uint16_t;

		virtual void upload() override;

		virtual void offload() override;

		static auto combine_shader_files(const std::filesystem::path &_vs_path, const std::filesystem::path &_fs_path
		                                 , const std::filesystem::path &_target) -> bool;

	private:
		std::vector<std::byte> vertex_shader_bytecode_ = {};
		std::vector<std::byte> fragment_shader_bytecode_ = {};
		std::optional<std::string> vertex_shader_textcode_ = {};
		std::optional<std::string> fragment_shader_textcode_ = {};

		struct {
			std::uint16_t program_id = 0;
			std::uint16_t sampler_uniform_id = 0;
		} volatile_upload_data_;
	};

	class ShaderImporteur final : public ResourceImporteur<ShaderImporteur, Shader> {
	public:
		auto load(std::filesystem::path &&_path) const -> std::shared_ptr<Shader>;
	};

	class ShaderCompiler final : public ResourceImporteur<ShaderCompiler, Shader> {
	public:
		auto load(std::filesystem::path &&_path) const -> std::shared_ptr<Shader>;
	};
}
