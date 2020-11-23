// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: pybase.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 23.11.2020 17:54

#pragma once

#include <string>
#include <filesystem>

namespace dce::scripting::py {
	extern auto initialize(const char* const _program_name, const char* const _std_dir, const char* const _home_dir, const char*& _out_info, const char** const _argv, const int _argc) -> bool;
	extern void shutdown();
	extern auto exec_string(const std::string& _script_text) -> bool;
	extern auto exec_file(const std::filesystem::path& _path) -> bool;
	extern auto exec_test_file(const std::filesystem::path& _path) -> std::tuple<bool, std::string>;
}
