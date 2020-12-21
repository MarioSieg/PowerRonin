#pragma once

#include <filesystem>

#include "gl_headers.hpp"
#include "gpu.hpp"
#include "views.hpp"

namespace dce::renderer {
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
}
