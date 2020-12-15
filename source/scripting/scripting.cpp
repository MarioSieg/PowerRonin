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
#include "scripting.hpp"
#include "internal_calls.hpp"
#include "dreamcast.dll.hpp"

namespace dce::scripting {
	Scripting::Scripting() : ISubsystem("Scripting", EVENTS) { }

	auto Scripting::on_pre_startup(Runtime& _rt) -> bool {

		auto& proto = _rt.protocol();
		const auto lib_dir = _rt.config().scripting.library_dir.string();
		const auto cfg_dir = _rt.config().scripting.config_dir.string();

		proto.info("Initializing scripting backend (Mono)...");
		proto.info("Library dir: {}, config dir: {}", lib_dir, cfg_dir);

		this->runtime_environment_.initialize(lib_dir, cfg_dir);
		this->dreamcast_core_assembly_.load(std::string(DREAMCAST_DLL_NAME), this->runtime_environment_);

		this->engine_class_ = mono_class_from_name(this->dreamcast_core_assembly_.get_image(), "Dreamcast.Core", "Core");
		[[unlikely]] if (!this->engine_class_) {
			return false;
		}

		register_basic_internal_calls(_rt);

		this->engine_on_start_ = mono_class_get_method_from_name(this->engine_class_, "OnSystemStart", 0);
		[[unlikely]] if (!this->engine_on_start_) {
			return false;
		}

		this->engine_on_update_ = mono_class_get_method_from_name(this->engine_class_, "OnSystemUpdate", 0);
		[[unlikely]] if (!this->engine_on_update_) {
			return false;
		}

		this->engine_on_exit_ = mono_class_get_method_from_name(this->engine_class_, "OnSystemExit", 0);
		[[unlikely]] if (!this->engine_on_exit_) {
			return false;
		}

		MonoObject* ex = nullptr;
		auto* ret = mono_runtime_invoke(this->engine_on_start_, nullptr, nullptr, &ex);
		[[unlikely]] if (ex) {
			MonoString* mono_msg = mono_object_to_string(ex, nullptr);
			char* msg = mono_string_to_utf8(mono_msg);
			_rt.scripting_protocol().error(msg);
			mono_free(msg);
		}

		return true;
	}

	auto Scripting::on_post_startup(Runtime& _rt) -> bool {
		return true;
	}

	auto Scripting::on_pre_tick(Runtime& _rt) -> bool {

		MonoObject* ex = nullptr;
		auto* ret = mono_runtime_invoke(this->engine_on_update_, nullptr, nullptr, &ex);
		[[unlikely]] if (ex) {
			MonoString* mono_msg = mono_object_to_string(ex, nullptr);
			char* msg = mono_string_to_utf8(mono_msg);
			_rt.scripting_protocol().error(msg);
			mono_free(msg);
		}
		return !ret && !ex;
	}

	auto Scripting::on_post_tick(Runtime& _rt) -> bool {
		return true;
	}

	auto Scripting::on_pre_shutdown(Runtime& _rt) -> bool {
		MonoObject* ex = nullptr;
		auto* ret = mono_runtime_invoke(this->engine_on_exit_, nullptr, nullptr, &ex);
		[[unlikely]] if (ex) {
			MonoString* mono_msg = mono_object_to_string(ex, nullptr);
			char* msg = mono_string_to_utf8(mono_msg);
			_rt.scripting_protocol().error(msg);
			mono_free(msg);
		}
		this->dreamcast_core_assembly_.unload();
		this->runtime_environment_.shutdown();
		return true;
	}

	auto Scripting::on_post_shutdown(Runtime& _rt) -> bool {
		return true;
	}
}
