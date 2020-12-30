#include "../include/dce/shader.hpp"
#include "../include/dce/blob.hpp"
#include "renderer/gl_headers.hpp"

namespace dce {
	void Shader::upload() {
		[[unlikely]] if (this->is_uploaded_) {
			this->offload();
		}

		[[unlikely]] if (this->vertex_shader_bytecode_.empty() || this->fragment_shader_bytecode_ && (*this->
			fragment_shader_bytecode_).empty()) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload shader!");
		}

		const auto* const vs_mem = bgfx::makeRef(this->vertex_shader_bytecode_.data()
		                                         , static_cast<std::uint32_t>(this->vertex_shader_bytecode_.size() *
			                                         sizeof(
				                                         std::byte)), nullptr, nullptr);

		[[unlikely]] if (!vs_mem) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload shader!");
		}

		const bgfx::ShaderHandle vs = createShader(vs_mem);
		[[unlikely]] if (!isValid(vs)) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload shader!");
		}

		auto fs = bgfx::ShaderHandle{bgfx::kInvalidHandle};

		[[likely]] if (this->fragment_shader_bytecode_) {
			const auto* const fs_mem = bgfx::makeRef((*this->fragment_shader_bytecode_).data()
			                                         , static_cast<std::uint32_t>((*this->fragment_shader_bytecode_).
				                                         size() * sizeof
				                                         (std::byte)), nullptr, nullptr);

			[[unlikely]] if (!fs_mem) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload shader!");
			}

			fs = createShader(fs_mem);
			[[unlikely]] if (!isValid(fs)) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload shader!");
			}
		}

		const bgfx::ProgramHandle shader = createProgram(vs, fs, true);
		[[unlikely]] if (!isValid(shader)) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload shader!");
		}

		this->volatile_upload_data_.program_id = shader.idx;

		this->is_uploaded_ = true;
	}

	void Shader::offload() {
		const auto program_handle = bgfx::ProgramHandle{this->volatile_upload_data_.program_id};
		[[likely]] if (isValid(program_handle)) {
			destroy(program_handle);
		}
		this->volatile_upload_data_.program_id = bgfx::kInvalidHandle;
		this->is_uploaded_ = false;
	}

	auto ShaderImporteur::load(std::filesystem::path&& _path
	                           , const ShaderMeta* const _meta) const -> std::shared_ptr<Shader> {
		[[unlikely]] if (_path.extension() != Shader::FILE_EXTENSIONS[0]) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader from file!");
		}

		Blob vs_bytecode = {};
		blob_from_disk(_path, vs_bytecode);
		[[unlikely]] if (vs_bytecode.empty()) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load shader from file!");
		}

		Blob fs_bytecode = {};
		const auto fragment_file = _path.replace_filename("fragment.shc");
		[[likely]] if (is_regular_file(fragment_file)) {
			blob_from_disk(fragment_file, fs_bytecode);
		}

		auto self = IResource<ShaderMeta>::allocate<Shader>();
		self->file_path_ = std::move(_path);
		self->vertex_shader_bytecode_ = std::move(vs_bytecode);
		self->vertex_shader_textcode_ = std::nullopt;
		self->fragment_shader_bytecode_ = std::nullopt;
		[[likely]] if (!fs_bytecode.empty()) {
			self->fragment_shader_bytecode_ = std::move(fs_bytecode);
		}
		self->fragment_shader_textcode_ = std::nullopt;
		self->meta_data_ = _meta ? *_meta : IResource<ShaderMeta>::load_meta_or_default(self->file_path_);

		self->upload();

		return self;
	}

	auto ShaderCompiler::load(std::filesystem::path&& _path,
	                          const ShaderMeta* const _meta) const -> std::shared_ptr<Shader> {
		auto self = IResource<ShaderMeta>::allocate<Shader>();

		self->file_path_ = std::move(_path);
		self->meta_data_ = _meta ? *_meta : IResource<ShaderMeta>::load_meta_or_default(self->file_path_);

		self->upload();

		return self;
	}
}
