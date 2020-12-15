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

#include "../../include/dce/procinfo.hpp"
#include "../../include/dce/except.hpp"
#include "environment.hpp"
#include <filesystem>

namespace dce::scripting {
	void default_exception_handler(AsyncProtocol& _proto, MonoObject* const _ex) {
		MonoObject* ex = nullptr;
		MonoString* const mono_msg = mono_object_to_string(_ex, &ex);
		[[likely]] if (!ex && mono_msg) {
			char* const msg = mono_string_to_utf8(mono_msg);
			_proto.error(msg);
			mono_free(msg);
		}
	}

	void RuntimeEnvironment::initialize(const std::string_view _lib_dir, const std::string_view _cfg_dir) {
		mono_set_dirs(_lib_dir.data(), _cfg_dir.data());
		mono_config_parse(nullptr);
		const auto exe_name = get_executable_name();
		this->domain_ = mono_jit_init(exe_name.c_str());
		[[unlikely]] if (!this->domain_) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to initialize domain!");
		}
	}

	void RuntimeEnvironment::shutdown() {
		mono_jit_cleanup(this->domain_);
		this->domain_ = nullptr;
	}
}
