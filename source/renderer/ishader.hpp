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
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

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
