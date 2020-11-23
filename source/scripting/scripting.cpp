// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: scripting.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 23.11.2020 10:02

#include "scripting.hpp"
#include "../../include/dce/utils.hpp"
#include "py/pybase.hpp"
#include "py/pystreamhook.hpp"

namespace dce::scripting {

	Scripting::Scripting() : ISubsystem("Scripting", EVENTS) { }

	auto Scripting::on_pre_startup(State& _state) -> bool {
		auto& proto = _state.protocol();
		const auto& config = _state.config();

		this->startup_python_runtime(proto, config);

		return true;
	}

	auto Scripting::on_post_startup(State& _state) -> bool {
		return true;
	}

	auto Scripting::on_pre_tick(State& _state) -> bool {
		return true;
	}

	auto Scripting::on_post_tick(State& _state) -> bool {
		return true;
	}

	auto Scripting::on_pre_shutdown(State& _state) -> bool {
		return true;
	}

	auto Scripting::on_post_shutdown(State& _state) -> bool {
		py::reset_hook();
		py::shutdown();
		return true;
	}

	void Scripting::startup_python_runtime(AsyncProtocol& _proto, const Config& _config) const {
		const auto py_libs = _config.scripting.python_libs_dir.string();
		const auto program_name = get_executable_name();
		const char* info;

		py::stdout_pre_initialize();
		py::initialize(program_name.c_str(), py_libs.c_str(), py_libs.c_str(), info, nullptr, 0);
		py::stdout_post_initialize();
		py::stdout_install_hook([&_proto](std::string&& _msg) {
			[[likely]] if (!_msg.empty()) {
				_proto.info(std::move(_msg));
			}
		});

		_proto.critical("Initializing Python {}...", info);
		_proto.critical("Running test Python script \"{}\"...", _config.scripting.python_test_script.string());
		const auto result = py::exec_test_file(_config.scripting.python_test_script);
		[[unlikely]] if (!std::get<0>(result)) {
			_proto.error("Failed to execute test script!");
		}
	}
}
