#pragma once

#include "IResource.hpp"
#include "MathLib.hpp"
#include <optional>
#include <unordered_map>
#include <tuple>

#include "Blob.hpp"

namespace PowerRonin
{
	enum class UniformType
	{
		SAMPLER,
		VEC_4,
		MATRIX_3x3,
		MATRIX_4x4,
	};

	struct ShaderMeta final : ISerializable
	{
		virtual inline void serialize(JsonStream&) const override { }

		virtual inline void deserialize(const JsonStream&) override { }
	};

	/* Represents a shader program with vertex and fragmet shader. */
	class Shader final : public IResource<ShaderMeta>
	{
		friend class ShaderImporteur;
		friend class ShaderCompiler;

	public:
		/* All associated file types. */
		static constexpr std::array<std::string_view, 4> FILE_EXTENSIONS = {".shc", ".shb"};

		[[nodiscard]] auto vertex_shader_bytecode() const noexcept -> const Blob&;

		[[nodiscard]] auto fragment_shader_bytecode() const noexcept -> const std::optional<Blob>&;

		[[nodiscard]] auto vertex_shader_textcode() const noexcept -> const std::optional<std::string>&;

		[[nodiscard]] auto fragment_shader_textcode() const noexcept -> const std::optional<std::string>&;

		[[nodiscard]] auto program_id() const noexcept -> std::uint16_t;

		virtual void Upload() override;

		virtual void Offload() override;

	private:
		Blob vertex_shader_bytecode_ = {};
		std::optional<Blob> fragment_shader_bytecode_ = {};
		std::optional<std::string> vertex_shader_textcode_ = {};
		std::optional<std::string> fragment_shader_textcode_ = {};

		struct
		{
			std::uint16_t program_id = 0;
		} volatile_upload_data_;
	};

	class ShaderImporteur final : public ResourceImporteur<ShaderImporteur, Shader>
	{
	public:
		auto load(std::filesystem::path&& _path
		          , const ShaderMeta* const _meta = nullptr) const -> std::shared_ptr<Shader>;
	};

	class ShaderCompiler final : public ResourceImporteur<ShaderCompiler, Shader>
	{
	public:
		auto load(std::filesystem::path&& _path,
		          const ShaderMeta* const _meta = nullptr) const -> std::shared_ptr<Shader>;
	};
}
