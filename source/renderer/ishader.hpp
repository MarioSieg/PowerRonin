// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: ishader.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 19.11.2020 18:52

#pragma once

#include <filesystem>

#include "gl_headers.hpp"
#include "program_loader.hpp"
#include "gpu.hpp"

#include "../../include/dce/mesh_renderer.hpp"
#include "../../include/dce/material.hpp"

namespace dce::renderer {
	template <typename Material>
	class IShader {
	public:
		explicit IShader(const std::string_view _name) noexcept;
		IShader(const IShader &) = delete;
		IShader(IShader &&) = delete;
		auto operator=(const IShader &) -> IShader& = delete;
		auto operator=(IShader &&) -> IShader& = delete;
		virtual ~IShader() = default;

		[[nodiscard]] auto get_name() const noexcept -> std::string_view;

		[[nodiscard]] auto get_path() const noexcept -> const std::filesystem::path&;

		virtual void load();
		virtual void unload();
		virtual void draw(GPU &_gpu, const Mesh &_mesh, const Material &_mat) = 0;

	protected:
		std::string_view name_ = {};
		std::filesystem::path path_ = {};
		bgfx::ProgramHandle program_ = {bgfx::kInvalidHandle};
	};

	template <typename Material>
	IShader<Material>::IShader(const std::string_view _name) noexcept : name_(_name) { }

	template <typename Material>
	inline auto IShader<Material>::get_name() const noexcept -> std::string_view {
		return this->name_;
	}

	template <typename Material>
	inline auto IShader<Material>::get_path() const noexcept -> const std::filesystem::path& {
		return this->path_;
	}

	template <typename Material>
	inline void IShader<Material>::load() {
		this->program_ = load_shader_program(this->name_);
	}

	template <typename Material>
	inline void IShader<Material>::unload() {
		BGFX_FREE(this->program_);
	}
}
