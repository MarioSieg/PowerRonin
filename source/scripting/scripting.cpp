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

#include "../../extern/python/cpython-3.6.12/Include/Python.h"

namespace dce::scripting {

	Scripting::Scripting() : ISubsystem("Scripting", EVENTS) { }

	constexpr std::string_view TEST_SCRIPT = R"(
		from time import time, ctime
		print("Hello world from the Dreamcast Engine embedded Python!")
		print("Today is ", ctime(time()))
	)";

	auto Scripting::on_pre_startup(State& _state) -> bool {
		const std::wstring py_libs = L"scripts/python/pystd";


		auto& proto = _state.protocol();

		proto.info("Initializing Python {}...", Py_GetVersion());

		proto.info("Pylib: {}", std::string(py_libs.begin(), py_libs.end()));

		const auto program_name = get_executable_name();

		wchar_t* name = Py_DecodeLocale(program_name.c_str(), nullptr);

		Py_SetProgramName(name);
		Py_SetPath(py_libs.c_str());
		Py_Initialize();

		proto.info("Running mini test Python script:\n{}", TEST_SCRIPT);

		PyRun_SimpleString(TEST_SCRIPT.data());

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
		Py_FinalizeEx();
		return true;
	}
}
