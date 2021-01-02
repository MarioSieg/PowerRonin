#include "../include/dce/shader.hpp"
#include "../include/dce/blob.hpp"
#include "renderer/gl_headers.hpp"

namespace dce
{
	void Shader::upload()
	{
		if (this->is_uploaded_) [[unlikely]]
		{
			this->offload();
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

		this->is_uploaded_ = true;
	}

	void Shader::offload()
	{
		const auto program_handle = bgfx::ProgramHandle{this->volatile_upload_data_.program_id};
		if (isValid(program_handle)) [[likely]]
		{
			destroy(program_handle);
		}
		this->volatile_upload_data_.program_id = bgfx::kInvalidHandle;
		this->is_uploaded_ = false;
	}

	auto ShaderImporteur::load(std::filesystem::path&& _path
	                           , const ShaderMeta* const _meta) const -> std::shared_ptr<Shader>
	{
		if (_path.extension() != Shader::FILE_EXTENSIONS[0]) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader from file!");
		}

		Blob vs_bytecode = {};
		blob_from_disk(_path, vs_bytecode);
		if (vs_bytecode.empty()) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader from file!");
		}

		Blob fs_bytecode = {};
		const auto fragment_file = _path.replace_filename("fragment.shc");
		if (is_regular_file(fragment_file)) [[likely]]
		{
			blob_from_disk(fragment_file, fs_bytecode);
		}

		auto self = IResource<ShaderMeta>::allocate<Shader>();
		self->file_path_ = std::move(_path);
		self->vertex_shader_bytecode_ = std::move(vs_bytecode);
		self->vertex_shader_textcode_ = std::nullopt;
		self->fragment_shader_bytecode_ = std::nullopt;
		if (!fs_bytecode.empty()) [[likely]]
		{
			self->fragment_shader_bytecode_ = std::move(fs_bytecode);
		}
		self->fragment_shader_textcode_ = std::nullopt;
		self->meta_data_ = _meta ? *_meta : IResource<ShaderMeta>::load_meta_or_default(self->file_path_);

		self->upload();

		return self;
	}

	auto ShaderCompiler::load(std::filesystem::path&& _path,
	                          const ShaderMeta* const _meta) const -> std::shared_ptr<Shader>
	{
		auto self = IResource<ShaderMeta>::allocate<Shader>();

		self->file_path_ = std::move(_path);
		self->meta_data_ = _meta ? *_meta : IResource<ShaderMeta>::load_meta_or_default(self->file_path_);

		self->upload();

		return self;
	}
}
