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

#include "ishader.hpp"
#include "program_loader.hpp"

namespace dce::renderer {

	IShader::IShader(const std::string_view _name, GPU& _gpu) noexcept : name_(_name), gpu_(_gpu) {}

	auto IShader::get_name() const noexcept -> std::string_view {
		return this->name_;
	}

	auto IShader::get_path() const noexcept -> const std::filesystem::path& {
		return this->path_;
	}

	void IShader::load() {
		this->program_ = load_shader_program(this->name_);
	}

	void IShader::unload() {
		BGFX_FREE(this->program_);
	}
}
