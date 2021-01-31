// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#include "scripting.hpp"
#include "internal_calls.hpp"
#include "power_ronin.dll.hpp"

namespace PowerRonin::Scripting
{
	ScriptingSystem::ScriptingSystem() : ISubsystem("Scripting", EVENTS), runtime_environment_() { }

	void ScriptingSystem::OnPreStartup(Runtime& runtime)
	{
		auto& proto = runtime.Protocol();
		const auto lib_dir = runtime.Config().Scripting.LibraryDir.string();
		const auto cfg_dir = runtime.Config().Scripting.ConfigDir.string();

		proto.Info("Initializing scripting backend (Mono)...");
		proto.Info("Library dir: {}, config dir: {}", lib_dir, cfg_dir);

		this->runtime_environment_.initialize(lib_dir, cfg_dir);
		this->runtime_environment_.exception_hook = [&runtime](auto* const exception)
		{
			default_exception_handler(runtime.ScriptingProtocol(), exception);
		};

		this->core_assembly_.load(std::string(ASSEMBLY_NAME_ID), this->runtime_environment_);

		register_basic_internal_calls(runtime);

		this->setup_hooks();

		runtime.TerminalHook() = [this](char* const _str)
		{
			void* params[] = {mono_string_new(this->runtime_environment_.get_domain(), _str)};
			this->command_db_.on_command_enter(this->runtime_environment_, params);
		};

		this->core_.on_pre_startup(this->runtime_environment_);
	}

	void ScriptingSystem::OnPostStartup(Runtime&)
	{
		this->core_.on_post_startup(this->runtime_environment_);
	}

	void ScriptingSystem::OnPreTick(Runtime&)
	{
		this->core_.on_pre_tick(this->runtime_environment_);
	}

	void ScriptingSystem::OnPostTick(Runtime&)
	{
		this->core_.on_post_tick(this->runtime_environment_);;
	}

	void ScriptingSystem::OnPreShutdown(Runtime&)
	{
		this->core_.on_pre_shutdown(this->runtime_environment_);
	}

	void ScriptingSystem::OnPostShutdown(Runtime&)
	{
		this->core_.on_post_shutdown(this->runtime_environment_);
		this->core_assembly_.unload();
		this->runtime_environment_.shutdown();
	}

	void ScriptingSystem::setup_hooks()
	{
		this->core_.klass.load_from_name(this->core_assembly_, ASSEMBLY_NAMESPACE_ID, CORE_CLASS_ID);

		this->core_.on_pre_startup.query_from_class(this->core_.klass, CORE_ON_PRE_STARTUP_ID);
		this->core_.on_post_startup.query_from_class(this->core_.klass, CORE_ON_POST_STARTUP_ID);

		this->core_.on_pre_tick.query_from_class(this->core_.klass, CORE_ON_PRE_TICK_ID);
		this->core_.on_post_tick.query_from_class(this->core_.klass, CORE_ON_POST_TICK_ID);

		this->core_.on_pre_shutdown.query_from_class(this->core_.klass, CORE_PRE_SHUTDOWN_ID);
		this->core_.on_post_shutdown.query_from_class(this->core_.klass, CORE_POST_SHUTDOWN_ID);

		this->command_db_.klass.load_from_name(this->core_assembly_, ASSEMBLY_NAMESPACE_ID, COMMAND_DB_CLASS_ID);
		this->command_db_.on_command_enter.query_from_class(this->command_db_.klass, COMMAND_DB_CMD_ENTER_ID
		                                                    , COMMAND_DB_CMD_ENTER_PARAMS);
	}
}
