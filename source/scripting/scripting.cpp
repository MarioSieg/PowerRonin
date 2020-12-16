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
#include "dreamcast.dll.hpp"

namespace dce::scripting {
	Scripting::Scripting() : ISubsystem("Scripting", EVENTS), runtime_environment_() { }

	auto Scripting::on_pre_startup(Runtime& _rt) -> bool {

		auto& proto = _rt.protocol();
		const auto lib_dir = _rt.config().scripting.library_dir.string();
		const auto cfg_dir = _rt.config().scripting.config_dir.string();

		proto.info("Initializing scripting backend (Mono)...");
		proto.info("Library dir: {}, config dir: {}", lib_dir, cfg_dir);

		this->runtime_environment_.initialize(lib_dir, cfg_dir);
		this->runtime_environment_.exception_hook = [&_rt](auto* const _ex) {
			default_exception_handler(_rt.scripting_protocol(), _ex);
		};
		this->dreamcast_core_assembly_.load(std::string(DREAMCAST_DLL_NAME), this->runtime_environment_);
		this->core_class_.load_from_name(this->dreamcast_core_assembly_, DREAMCAST_DLL_CORE_CLASS_NAMESPACE, DREAMCAST_DLL_CORE_CLASS);

		register_basic_internal_calls(_rt);

		this->on_start_.query_from_class(this->core_class_, DREAMCAST_DLL_CORE_START);
		this->on_update_.query_from_class(this->core_class_, DREAMCAST_DLL_CORE_UPDATE);
		this->on_exit_.query_from_class(this->core_class_, DREAMCAST_DLL_CORE_EXIT);

		this->on_start_(this->runtime_environment_);

		return true;
	}

	auto Scripting::on_post_startup(Runtime& _rt) -> bool {
		return true;
	}

	auto Scripting::on_pre_tick(Runtime& _rt) -> bool {
		this->on_update_.call(this->runtime_environment_);
		return true;
	}

	auto Scripting::on_post_tick(Runtime& _rt) -> bool {
		return true;
	}

	auto Scripting::on_pre_shutdown(Runtime& _rt) -> bool {
		this->on_update_.call(this->runtime_environment_);
		this->dreamcast_core_assembly_.unload();
		this->runtime_environment_.shutdown();
		return true;
	}

	auto Scripting::on_post_shutdown(Runtime& _rt) -> bool {
		return true;
	}
}
