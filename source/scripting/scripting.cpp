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

#include "scripting.hpp"
#include "../../include/dce/procinfo.hpp"

namespace dce::scripting {
	Scripting::Scripting() : ISubsystem("Scripting", EVENTS) { }

	auto Scripting::on_pre_startup(Runtime& _rt) -> bool {

		auto& proto = _rt.protocol();

		mono_set_dirs("extern/mono/lib", "extern/mono/etc");
		mono_config_parse(nullptr);

		const auto exe_name = get_executable_name();
		this->domain_ = mono_jit_init(exe_name.c_str());

		return true;
	}

	auto Scripting::on_post_startup(Runtime& _rt) -> bool {
		return true;
	}

	auto Scripting::on_pre_tick(Runtime& _rt) -> bool {
		return true;
	}

	auto Scripting::on_post_tick(Runtime& _rt) -> bool {
		return true;
	}

	auto Scripting::on_pre_shutdown(Runtime& _rt) -> bool {
		return true;
	}

	auto Scripting::on_post_shutdown(Runtime& _rt) -> bool {
		return true;
	}
}
