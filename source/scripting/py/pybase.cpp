// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: pybase.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 23.11.2020 17:54

#include "pybase.hpp"
#include "python.hpp"
#include <fstream>

namespace dce::scripting::py {
	auto initialize(const char* const _program_name, const char* const _std_dir, const char* const _home_dir, const char*& _out_info, const char** const _argv, const int _argc) -> bool {
		wchar_t* name = Py_DecodeLocale(_program_name, nullptr);
		Py_SetProgramName(name);
		Py_SetPath(Py_DecodeLocale(_std_dir, nullptr));
		Py_SetPythonHome(Py_DecodeLocale(_home_dir, nullptr));
		[[likely]] if (_argv && _argc) {
			/* TODO This was ported from my old C code. */
			auto** buffer = static_cast<wchar_t**>(malloc(sizeof(wchar_t*) * _argc));
			for (auto i = 0; i < _argc; ++i) {
				*(buffer + i) = Py_DecodeLocale(*(_argv + i), nullptr);
			}
			PySys_SetArgvEx(_argc, buffer, 0);
			free(buffer);
		}
		Py_Initialize();
		_out_info = Py_GetVersion();
		return Py_IsInitialized();
	}

	void shutdown() {
		Py_Finalize();
	}

	auto exec_string(const std::string& _script_text) -> bool {
		return PyRun_SimpleString(_script_text.c_str()) == 0;
	}

	auto exec_file(const std::filesystem::path& _path) -> bool {
		std::ifstream file(_path);
		[[unlikely]] if (!file) {
			return false;
		}
		const auto script = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
		return exec_string(script);
	}

	auto exec_test_file(const std::filesystem::path& _path) -> std::tuple<bool, std::string> {
		std::ifstream file(_path);
		[[unlikely]] if (!file) {
			return {false, {}};
		}
		const auto script = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
		const bool result = exec_string(script);
		return std::make_tuple(result, script);
	}
}
