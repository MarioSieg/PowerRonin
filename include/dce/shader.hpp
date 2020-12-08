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

#pragma once

#include "resource.hpp"
#include "mathlib.hpp"
#include <optional>
#include <unordered_map>
#include <tuple>

namespace dce {
	enum class UniformType {
		SAMPLER
		, VEC_4
		, MATRIX_3x3
		, MATRIX_4x4
		,
	};

	struct ShaderMeta final : ISerializable {
		[[nodiscard]] inline virtual void serialize(JsonStream&) const override { }

		[[nodiscard]] inline virtual void deserialize(const JsonStream&) override { }
	};

	/* Represents a shader program with vertex and fragmet shader. */
	class Shader final : public IResource<ShaderMeta> {
		friend class ShaderImporteur;
		friend class ShaderCompiler;

	public:
		/* All associated file types. */
		static constexpr std::array<std::string_view, 4> FILE_EXTENSIONS = {".shc", ".shb"};

		[[nodiscard]] auto get_vertex_shader_bytecode() const noexcept -> const std::vector<std::byte>&;

		[[nodiscard]] auto get_fragment_shader_bytecode() const noexcept -> const std::optional<std::vector<std::byte>>&;

		[[nodiscard]] auto get_vertex_shader_textcode() const noexcept -> const std::optional<std::string>&;

		[[nodiscard]] auto get_fragment_shader_textcode() const noexcept -> const std::optional<std::string>&;

		[[nodiscard]] auto get_program_id() const noexcept -> std::uint16_t;

		[[nodiscard]] auto get_uniforms() const noexcept -> const std::unordered_map<
			std::string_view, std::tuple<UniformType, std::uint16_t>>&;

		void set_uniform(std::string_view _name, const Vector4<>& _value) const noexcept;
		void set_uniform(std::string_view _name, const Matrix3x3<>& _value) const noexcept;
		void set_uniform(std::string_view _name, const Matrix4x4<>& _value) const noexcept;
		void set_uniform(std::string_view _name, const float (&_value)[4]) const noexcept;
		void set_uniform(std::string_view _name, const float (&_value)[9]) const noexcept;
		void set_uniform(std::string_view _name, const float (&_value)[16]) const noexcept;

		[[nodiscard]] auto get_uniform_handle(std::string_view _name) const noexcept -> std::uint16_t;

		virtual void upload() override;

		virtual void offload() override;

	private:
		std::vector<std::byte> vertex_shader_bytecode_ = {};
		std::optional<std::vector<std::byte>> fragment_shader_bytecode_ = {};
		std::optional<std::string> vertex_shader_textcode_ = {};
		std::optional<std::string> fragment_shader_textcode_ = {};

		struct {
			std::uint16_t program_id = 0;
			std::unordered_map<std::string_view, std::tuple<UniformType, std::uint16_t>> uniforms = {};
		} volatile_upload_data_;
	};

	class ShaderImporteur final : public ResourceImporteur<ShaderImporteur, Shader> {
	public:
		auto load(std::filesystem::path&& _path
		          , std::unordered_map<std::string_view, std::tuple<UniformType, std::uint16_t>>&& _uniforms
		          , const ShaderMeta* const _meta = nullptr) const -> std::shared_ptr<Shader>;
	};

	class ShaderCompiler final : public ResourceImporteur<ShaderCompiler, Shader> {
	public:
		auto load(std::filesystem::path&& _path, const ShaderMeta* const _meta = nullptr) const -> std::shared_ptr<Shader>;
	};
}
