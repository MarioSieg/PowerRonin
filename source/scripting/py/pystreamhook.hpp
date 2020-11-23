// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: pystreamhook.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 23.11.2020 21:23

#pragma once

#include <functional>
#include <string>
#include "python.hpp"

namespace dce::scripting::py {
	using StreamHook = std::function<void(std::string&&)>;

	struct StdoutStream final {
		PyObject_HEAD
		StreamHook hook;
	};

	extern auto stdout_write(PyObject* const _self, PyObject* const _args) -> PyObject*;
	extern auto stdout_flush([[maybe_unused]] PyObject* const _self, [[maybe_unused]] PyObject* const _args) -> PyObject*;
	PyMODINIT_FUNC stdout_init();
	extern void stdout_pre_initialize();
	extern void stdout_post_initialize();
	extern void stdout_install_hook(const StreamHook& _hook);
	extern void reset_hook();
}
