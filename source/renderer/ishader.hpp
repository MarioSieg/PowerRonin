#pragma once

#include <filesystem>

#include "gl_headers.hpp"
#include "gpu.hpp"
#include "views.hpp"
#include "program_loader.hpp"

namespace dce::renderer {
	/// <summary>
	/// Base class for all shaders.
	/// </summary>
	/// <typeparam name="MatType">The type of material they draw.</typeparam>
	/// <typeparam name="InputType">The type of input they need (mesh).</typeparam>
	template <typename MatType, typename InputType = Mesh>
	class IShader {
	public:
		explicit IShader(std::string_view _name, GPU& _gpu) noexcept;
		IShader(const IShader&) = delete;
		IShader(IShader&&) = delete;
		auto operator=(const IShader&) -> IShader& = delete;
		auto operator=(IShader&&) -> IShader& = delete;
		virtual ~IShader() = default;

		using MatParams = Material;

		[[nodiscard]] auto get_name() const noexcept -> std::string_view;

		[[nodiscard]] auto get_path() const noexcept -> const std::filesystem::path&;

		virtual void load();

		virtual void unload();

	protected:
		std::string_view name_ = {};
		std::filesystem::path path_ = {};
		GPU& gpu_;
		bgfx::ProgramHandle program_ = {bgfx::kInvalidHandle};
	};

	template <typename MatType, typename Input>
	inline IShader<MatType, Input>::IShader(const std::string_view _name, GPU& _gpu) noexcept : name_(_name), gpu_(_gpu) {
	}

	template <typename MatType, typename Input>
	inline auto IShader<MatType, Input>::get_name() const noexcept -> std::string_view {
		return this->name_;
	}

	template <typename MatType, typename Input>
	inline auto IShader<MatType, Input>::get_path() const noexcept -> const std::filesystem::path& {
		return this->path_;
	}

	template <typename MatType, typename Input>
	inline void IShader<MatType, Input>::load() {
		this->program_ = load_shader_program(this->name_);
	}

	template <typename MatType, typename Input>
	inline void IShader<MatType, Input>::unload() {
		destroy(this->program_);
	}
}
