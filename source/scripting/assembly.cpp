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

#include "assembly.hpp"
#include <filesystem>
#include "../../include/dce/except.hpp"

namespace dce::scripting {
	void Assembly::load(std::string&& _name, RuntimeEnvironment& _env, const int _argc, char** const _argv) {
		_name = "runtime/" + _name + ".dll";
		[[unlikely]] if (!std::filesystem::exists(_name)) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Assembly file does not exist!");
		}

		MonoImageOpenStatus status = MONO_IMAGE_OK;

		this->assembly_ = mono_assembly_open(_name.c_str(), &status);

		[[unlikely]] if (status != MONO_IMAGE_OK || !this->assembly_) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to load assembly!");
		}

		this->image_ = mono_assembly_get_image(this->assembly_);

		[[unlikely]] if (!this->image_) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to fetch assembly image!");
		}

		[[unlikely]] if (!mono_jit_exec(_env.get_domain(), this->assembly_, _argc, _argv)) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to execute assembly entry!");
		}
	}

	void Assembly::unload() {
		mono_assembly_close(this->assembly_);
		this->assembly_ = nullptr;
	}
}
