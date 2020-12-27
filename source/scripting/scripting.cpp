#include "scripting.hpp"
#include "internal_calls.hpp"
#include "dreamcast.dll.hpp"

namespace dce::scripting {
	Scripting::Scripting() : ISubsystem("Scripting", EVENTS), runtime_environment_() {
	}

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

		this->core_assembly_.load(std::string(ASSEMBLY_NAME_ID), this->runtime_environment_);

		register_basic_internal_calls(_rt);

		this->setup_hooks();

		_rt.terminal_hook() = [this](char* const _str) {
			void* params[] = {mono_string_new(this->runtime_environment_.get_domain(), _str)};
			this->command_db_.on_command_enter(this->runtime_environment_, params);
		};

		this->core_.on_pre_startup(this->runtime_environment_);

		return true;
	}

	auto Scripting::on_post_startup(Runtime& _rt) -> bool {
		this->core_.on_post_startup(this->runtime_environment_);
		return true;
	}

	auto Scripting::on_pre_tick(Runtime& _rt) -> bool {
		this->core_.on_pre_tick(this->runtime_environment_);
		return true;
	}

	auto Scripting::on_post_tick(Runtime& _rt) -> bool {
		this->core_.on_post_tick(this->runtime_environment_);
		return true;
	}

	auto Scripting::on_pre_shutdown(Runtime& _rt) -> bool {
		this->core_.on_pre_shutdown(this->runtime_environment_);
		return true;
	}

	auto Scripting::on_post_shutdown(Runtime& _rt) -> bool {
		this->core_.on_post_shutdown(this->runtime_environment_);
		this->core_assembly_.unload();
		this->runtime_environment_.shutdown();
		return true;
	}

	void Scripting::setup_hooks() {
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
