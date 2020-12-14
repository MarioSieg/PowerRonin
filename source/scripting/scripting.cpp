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
#include "internal_calls.hpp"
#include "../../include/dce/procinfo.hpp"

namespace dce::scripting {
	Scripting::Scripting() : ISubsystem("Scripting", EVENTS) { }

	auto Scripting::on_pre_startup(Runtime& _rt) -> bool {

		auto& proto = _rt.protocol();
		const auto lib_dir = _rt.config().scripting.library_dir.string();
		const auto cfg_dir = _rt.config().scripting.config_dir.string();
		
		proto.info("Initializing scripting backend (Mono)...");
		proto.info("Library dir: {}, config dir: {}", lib_dir, cfg_dir);

		mono_set_dirs(lib_dir.c_str(), cfg_dir.c_str());
		mono_config_parse(nullptr);

		const auto exe_name = get_executable_name();
		this->domain_ = mono_jit_init(exe_name.c_str());

		[[unlikely]] if(!this->domain_) {
			return false;
		}

		this->engine_runtime_ = mono_domain_assembly_open(this->domain_, "bin/dreamcast.dll");
		[[unlikely]] if (!this->engine_runtime_) {
			return false;
		}

		this->engine_image_ = mono_assembly_get_image(this->engine_runtime_);
		[[unlikely]] if(!this->engine_image_) {
			return false;
		}

		int argc = 1;
		char* argv[1] = {
			const_cast<char*>("Test")
		};
		
		[[unlikely]] if(!mono_jit_exec(this->domain_, this->engine_runtime_, argc, argv)) {
			return false;
		}

		this->engine_class_ = mono_class_from_name(this->engine_image_, "Dreamcast", "Core");
		[[unlikely]] if(!this->engine_class_) {
			return false;
		}

		this->engine_instance_ = mono_object_new(this->domain_, this->engine_class_);
		[[unlikely]] if(!this->engine_instance_) {
			return false;
		}
		
		register_basic_internal_calls(_rt);
		mono_runtime_object_init(this->engine_instance_);

		this->engine_on_start_ = mono_class_get_method_from_name(this->engine_class_, "OnStart", 0);
		[[unlikely]] if(!this->engine_on_start_) {
			return false;
		}

		MonoObject* ex = nullptr;
		auto* ret = mono_runtime_invoke(this->engine_on_start_, this->engine_instance_, nullptr, &ex);
		[[unlikely]] if(ex) {
			mono_print_unhandled_exception(ex);
		}
		
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
