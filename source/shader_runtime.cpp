// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: shader_runtime.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "../include/dce/shader.hpp"
#include "../include/dce/blob.hpp"
#include "renderer/gl_headers.hpp"
#include <fstream>

namespace dce {
	void Shader::set_uniform(const std::string_view _name, const Matrix3x3<> &_value) const noexcept {
		assert(this->volatile_upload_data_.uniforms.contains(_name));
		const auto handle = bgfx::UniformHandle{std::get<1>(this->volatile_upload_data_.uniforms.at(_name))};
		assert(bgfx::isValid(handle));
		setUniform(handle, value_ptr(_value));
	}

	void Shader::set_uniform(const std::string_view _name, const Matrix4x4<> &_value) const noexcept {
		assert(this->volatile_upload_data_.uniforms.contains(_name));
		const auto handle = bgfx::UniformHandle{std::get<1>(this->volatile_upload_data_.uniforms.at(_name))};
		assert(bgfx::isValid(handle));
		setUniform(handle, value_ptr(_value));
	}

	void Shader::set_uniform(const std::string_view _name, const Vector4<> &_value) const noexcept {
		assert(this->volatile_upload_data_.uniforms.contains(_name));
		const auto handle = bgfx::UniformHandle{std::get<1>(this->volatile_upload_data_.uniforms.at(_name))};
		assert(bgfx::isValid(handle));
		setUniform(handle, value_ptr(_value));
	}

	void Shader::set_uniform(const std::string_view _name, const float ( &_value)[4]) const noexcept {
		assert(this->volatile_upload_data_.uniforms.contains(_name));
		const auto handle = bgfx::UniformHandle{std::get<1>(this->volatile_upload_data_.uniforms.at(_name))};
		assert(bgfx::isValid(handle));
		setUniform(handle, &*_value);
	}

	void Shader::set_uniform(const std::string_view _name, const float ( &_value)[9]) const noexcept {
		assert(this->volatile_upload_data_.uniforms.contains(_name));
		const auto handle = bgfx::UniformHandle{std::get<1>(this->volatile_upload_data_.uniforms.at(_name))};
		assert(bgfx::isValid(handle));
		setUniform(handle, &*_value);
	}

	void Shader::set_uniform(const std::string_view _name, const float ( &_value)[16]) const noexcept {
		assert(this->volatile_upload_data_.uniforms.contains(_name));
		const auto handle = bgfx::UniformHandle{std::get<1>(this->volatile_upload_data_.uniforms.at(_name))};
		assert(bgfx::isValid(handle));
		setUniform(handle, &*_value);
	}

	auto Shader::get_uniform_handle(const std::string_view _name) const noexcept -> std::uint16_t {
		assert(this->volatile_upload_data_.uniforms.contains(_name));
		return std::get<1>(this->volatile_upload_data_.uniforms.at(_name));
	}

	void Shader::upload() {
		[[unlikely]] if (this->uploaded_) {
			this->offload();
		}

		[[unlikely]] if (this->vertex_shader_bytecode_.empty() || this->fragment_shader_bytecode_ && (*this->
			fragment_shader_bytecode_).empty()) {
			throw std::runtime_error("Failed to upload shader!");
		}

		const auto *const vs_mem = bgfx::makeRef(this->vertex_shader_bytecode_.data()
		                                         , static_cast<std::uint32_t>(this->vertex_shader_bytecode_.size() * sizeof(
			                                         std::byte)), nullptr, nullptr);

		[[unlikely]] if (!vs_mem) {
			throw std::runtime_error("Failed to upload shader!");
		}

		const bgfx::ShaderHandle vs = createShader(vs_mem);
		[[unlikely]] if (!isValid(vs)) {
			throw std::runtime_error("Failed to upload shader!");
		}

		auto fs = bgfx::ShaderHandle{bgfx::kInvalidHandle};

		[[likely]] if (this->fragment_shader_bytecode_) {

			const auto *const fs_mem = bgfx::makeRef((*this->fragment_shader_bytecode_).data()
			                                         , static_cast<std::uint32_t>((*this->fragment_shader_bytecode_).size() *
				                                         sizeof(std::byte)), nullptr, nullptr);

			[[unlikely]] if (!fs_mem) {
				throw std::runtime_error("Failed to upload shader!");
			}

			fs = createShader(fs_mem);
			[[unlikely]] if (!isValid(fs)) {
				throw std::runtime_error("Failed to upload shader!");
			}

		}

		const bgfx::ProgramHandle shader = createProgram(vs, fs, true);
		[[unlikely]] if (!isValid(shader)) {
			throw std::runtime_error("Failed to upload shader!");
		}

		for (auto &[key, value] : this->volatile_upload_data_.uniforms) {
			[[unlikely]] if (key.empty()) {
				throw std::runtime_error("Failed to upload shader!");
			}
			bgfx::UniformType::Enum type = bgfx::UniformType::Sampler;
			switch (std::get<0>(value)) {
			case UniformType::SAMPLER: type = bgfx::UniformType::Sampler;
				break;
			case UniformType::VEC_4: type = bgfx::UniformType::Vec4;
				break;
			case UniformType::MATRIX_3x3: type = bgfx::UniformType::Mat3;
				break;
			case UniformType::MATRIX_4x4: type = bgfx::UniformType::Mat4;
				break;
			}
			const auto uniform_handle = createUniform(key.data(), type);
			[[unlikely]] if (!isValid(uniform_handle)) {
				throw std::runtime_error("Failed to upload shader!");
			}
			std::get<1>(value) = uniform_handle.idx;
		}

		this->volatile_upload_data_.program_id = shader.idx;

		this->uploaded_ = true;
	}

	void Shader::offload() {
		const auto program_handle = bgfx::ProgramHandle{this->volatile_upload_data_.program_id};
		[[likely]] if (isValid(program_handle)) {
			destroy(program_handle);
		}
		this->volatile_upload_data_.program_id = bgfx::kInvalidHandle;

		for (auto &uniform : this->volatile_upload_data_.uniforms) {
			const auto uniform_handle = bgfx::UniformHandle{std::get<1>(uniform.second)};
			[[likely]] if (isValid(uniform_handle)) {
				destroy(uniform_handle);
				std::get<1>(uniform.second) = bgfx::kInvalidHandle;
			}
		}
		this->uploaded_ = false;
	}

	auto ShaderImporteur::load(std::filesystem::path &&_path
	                           , std::unordered_map<std::string_view, std::tuple<UniformType, std::uint16_t>> &&_uniforms) const
	-> std::shared_ptr<Shader> {

		[[unlikely]] if (_path.extension() != Shader::FILE_EXTENSIONS[0]) {
			throw std::runtime_error("Failed to load shader from file!");
		}

		const std::ifstream stream(_path, std::ios::in | std::ios::binary);
		[[unlikely]] if (!stream) {
			throw std::runtime_error("Failed to load shader from file!");
		}

		Blob vs_bytecode = blob_from_disk(_path);
		[[unlikely]] if (vs_bytecode.empty()) {
			throw std::runtime_error("Failed to load shader from file!");
		}

		Blob fs_bytecode = {};
		const auto fragment_file = _path.replace_filename("fragment.shc");
		[[likely]] if (is_regular_file(fragment_file)) {
			fs_bytecode = blob_from_disk(fragment_file);
		}

		auto self = IResource::allocate<Shader>();
		self->file_path_ = std::move(_path);
		self->vertex_shader_bytecode_ = std::move(vs_bytecode);
		self->volatile_upload_data_.uniforms = std::move(_uniforms);
		self->vertex_shader_textcode_ = std::nullopt;
		self->fragment_shader_bytecode_ = std::nullopt;
		[[likely]] if (!fs_bytecode.empty()) {
			self->fragment_shader_bytecode_ = std::move(fs_bytecode);
		}
		self->fragment_shader_textcode_ = std::nullopt;

		self->upload();

		return self;
	}

	auto ShaderCompiler::load(std::filesystem::path &&_path) const -> std::shared_ptr<Shader> {

		auto self = IResource::allocate<Shader>();
		self->file_path_ = std::move(_path);

		self->upload();

		return self;
	}
}
