// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: shader_runtime.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 20:16

#include "../include/dce/shader.hpp"
#include "../include/dce/blob.hpp"
#include "renderer/bgfx_headers.hpp"
#include <fstream>

namespace dce {
	void Shader::upload() {
		if (this->uploaded_) {
			this->offload();
		}

		if (this->vertex_shader_bytecode_.empty() || this->fragment_shader_bytecode_.empty()) {
			throw std::runtime_error("Failed to upload shader!");
		}

		const auto *const vs_mem = bgfx::makeRef(this->vertex_shader_bytecode_.data()
		                                         , static_cast<std::uint32_t>(this->vertex_shader_bytecode_.size() * sizeof(
			                                         std::byte)), nullptr, nullptr);

		if (!vs_mem) {
			throw std::runtime_error("Failed to upload shader!");
		}

		const bgfx::ShaderHandle vs = createShader(vs_mem);
		if (!isValid(vs)) {
			throw std::runtime_error("Failed to upload shader!");
		}

		const auto *const fs_mem = bgfx::makeRef(this->fragment_shader_bytecode_.data()
		                                         , static_cast<std::uint32_t>(this->fragment_shader_bytecode_.size() * sizeof(
			                                         std::byte)), nullptr, nullptr);

		if (!fs_mem) {
			throw std::runtime_error("Failed to upload shader!");
		}

		const bgfx::ShaderHandle fs = createShader(fs_mem);
		if (!isValid(fs)) {
			throw std::runtime_error("Failed to upload shader!");
		}

		const bgfx::ProgramHandle shader = createProgram(vs, fs, true);
		if (!isValid(shader)) {
			throw std::runtime_error("Failed to upload shader!");
		}

		const bgfx::UniformHandle sampler_uniform = createUniform("s_texColor", bgfx::UniformType::Sampler);
		if (!isValid(sampler_uniform)) {
			throw std::runtime_error("Failed to upload shader!");
		}

		this->volatile_upload_data_.program_id = shader.idx;
		this->volatile_upload_data_.sampler_uniform_id = sampler_uniform.idx;

		this->uploaded_ = true;
	}

	void Shader::offload() {
		destroy(bgfx::ProgramHandle{this->volatile_upload_data_.program_id});
		destroy(bgfx::UniformHandle{this->volatile_upload_data_.sampler_uniform_id});
		this->uploaded_ = false;
	}

	auto Shader::combine_shader_files(const std::filesystem::path &_vs_path, const std::filesystem::path &_fs_path
	                                  , const std::filesystem::path &_target) -> bool {
		const Blob vs = blob_from_disk(_vs_path);
		if (vs.empty()) {
			return false;
		}
		const Blob fs = blob_from_disk(_fs_path);
		if (fs.empty()) {
			return false;
		}

		std::ofstream stream(_target, std::ios::binary | std::ios::out);
		if (!stream) {
			return false;
		}

		const auto vs_bytes_count = static_cast<std::uint64_t>(vs.size());
		const auto fs_bytes_count = static_cast<std::uint64_t>(fs.size());

		stream.write(reinterpret_cast<const char * const>(&vs_bytes_count), sizeof(std::uint64_t));
		stream.write(reinterpret_cast<const char * const>(&fs_bytes_count), sizeof(std::uint64_t));
		stream.write(reinterpret_cast<const char * const>(vs.data()), vs_bytes_count * sizeof(std::byte));
		stream.write(reinterpret_cast<const char * const>(fs.data()), fs_bytes_count * sizeof(std::byte));

		return true;
	}

	auto ShaderImporteur::load(std::filesystem::path &&_path) const -> std::shared_ptr<Shader> {
		std::ifstream stream(_path, std::ios::in | std::ios::binary);
		if (!stream) {
			throw std::runtime_error("Failed to load shader from file!");
		}
		std::uint64_t vs_bytes_count = 0;
		std::uint64_t fs_bytes_count = 0;

		stream.read(reinterpret_cast<char * const>(&vs_bytes_count), sizeof(std::uint64_t));
		stream.read(reinterpret_cast<char * const>(&fs_bytes_count), sizeof(std::uint64_t));

		if (!vs_bytes_count || !fs_bytes_count) {
			throw std::runtime_error("Failed to load shader from file!");
		}

		std::vector<std::byte> vs_bytecode = {};
		vs_bytecode.resize(vs_bytes_count / sizeof(std::byte));
		stream.read(reinterpret_cast<char * const>(vs_bytecode.data()), vs_bytes_count * sizeof(std::byte));
		if (!stream) {
			throw std::runtime_error("Failed to load shader from file!");
		}

		std::vector<std::byte> fs_bytecode = {};
		fs_bytecode.resize(fs_bytes_count / sizeof(std::byte));
		stream.read(reinterpret_cast<char * const>(fs_bytecode.data()), fs_bytes_count * sizeof(std::byte));
		if (!stream) {
			throw std::runtime_error("Failed to load shader from file!");
		}

		auto self = IResource::allocate<Shader>();
		self->file_path_ = std::move(_path);
		self->vertex_shader_bytecode_ = std::move(vs_bytecode);
		self->vertex_shader_textcode_ = std::nullopt;
		self->fragment_shader_bytecode_ = std::move(fs_bytecode);
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
