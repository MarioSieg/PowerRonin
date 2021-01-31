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

#include "../include/power_ronin/shader.hpp"
#include "../include/power_ronin/blob.hpp"
#include "renderer/gl_headers.hpp"

namespace PowerRonin
{
	void Shader::Upload()
	{
		if (this->isUploaded) [[unlikely]]
		{
			this->Offload();
		}

		if (this->vertex_shader_bytecode_.empty() || this->fragment_shader_bytecode_ && (*this->
			fragment_shader_bytecode_).empty()) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload shader!");
		}

		const auto* const vs_mem = bgfx::makeRef(this->vertex_shader_bytecode_.data()
		                                         , static_cast<std::uint32_t>(this->vertex_shader_bytecode_.size() *
			                                         sizeof(
				                                         std::byte)), nullptr, nullptr);

		if (!vs_mem) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload shader!");
		}

		const bgfx::ShaderHandle vs = createShader(vs_mem);
		if (!isValid(vs)) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload shader!");
		}

		auto fs = bgfx::ShaderHandle{bgfx::kInvalidHandle};

		if (this->fragment_shader_bytecode_) [[likely]]
		{
			const auto* const fs_mem = bgfx::makeRef((*this->fragment_shader_bytecode_).data()
			                                         , static_cast<std::uint32_t>((*this->fragment_shader_bytecode_).
				                                         size() * sizeof
				                                         (std::byte)), nullptr, nullptr);

			if (!fs_mem) [[unlikely]]
			{
				throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload shader!");
			}

			fs = createShader(fs_mem);
			if (!isValid(fs)) [[unlikely]]
			{
				throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload shader!");
			}
		}

		const bgfx::ProgramHandle shader = createProgram(vs, fs, true);
		if (!isValid(shader)) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload shader!");
		}

		this->volatile_upload_data_.program_id = shader.idx;

		this->isUploaded = true;
	}

	void Shader::Offload()
	{
		const auto program_handle = bgfx::ProgramHandle{this->volatile_upload_data_.program_id};
		if (isValid(program_handle)) [[likely]]
		{
			destroy(program_handle);
		}
		this->volatile_upload_data_.program_id = bgfx::kInvalidHandle;
		this->isUploaded = false;
	}

	auto ShaderImporteur::load(std::filesystem::path&& _path
	                           , const ShaderMeta* const _meta) const -> std::shared_ptr<Shader>
	{
		if (_path.extension() != Shader::FILE_EXTENSIONS[0]) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader from file!");
		}

		Blob vs_bytecode = {};
		ReadBlobFromDisk(_path, vs_bytecode);
		if (vs_bytecode.empty()) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader from file!");
		}

		Blob fs_bytecode = {};
		const auto fragment_file = _path.replace_filename("fragment.shc");
		if (is_regular_file(fragment_file)) [[likely]]
		{
			ReadBlobFromDisk(fragment_file, fs_bytecode);
		}

		auto self = IResource<ShaderMeta>::Allocate<Shader>();
		self->filePath = std::move(_path);
		self->vertex_shader_bytecode_ = std::move(vs_bytecode);
		self->vertex_shader_textcode_ = std::nullopt;
		self->fragment_shader_bytecode_ = std::nullopt;
		if (!fs_bytecode.empty()) [[likely]]
		{
			self->fragment_shader_bytecode_ = std::move(fs_bytecode);
		}
		self->fragment_shader_textcode_ = std::nullopt;
		self->metaData = _meta ? *_meta : IResource<ShaderMeta>::LoadMetaOrDefault(self->filePath);

		self->Upload();

		return self;
	}

	auto ShaderCompiler::load(std::filesystem::path&& _path,
	                          const ShaderMeta* const _meta) const -> std::shared_ptr<Shader>
	{
		auto self = IResource<ShaderMeta>::Allocate<Shader>();

		self->filePath = std::move(_path);
		self->metaData = _meta ? *_meta : IResource<ShaderMeta>::LoadMetaOrDefault(self->filePath);

		self->Upload();

		return self;
	}
}
