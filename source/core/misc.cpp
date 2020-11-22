// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: misc.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 22.11.2020 18:38

#include "../../include/dce/core/misc.hpp"
#include "../../include/dce/utils.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

namespace dce::core {

	void create_fatal_dump() {
		if (!std::filesystem::is_directory("crashes")) {
			std::filesystem::create_directory("crashes");
		}
		std::stringstream ss;
		const auto now = std::time(nullptr);
		const auto tm = safe_localtime(now);
		ss << "crashes/" << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S") << ".crash";
		std::ofstream file(ss.str());
		ss.str("");
		ss << "MSG: Fatal unknown error!";
		[[likely]] if (file) {
			file << ss.str();
		}
		std::cerr << ss.str();
	}

	void create_fatal_dump(const std::exception& _ex) {
		if (!std::filesystem::is_directory("crashes")) {
			std::filesystem::create_directory("crashes");
		}
		std::stringstream ss;
		const auto now = std::time(nullptr);
		const auto tm = safe_localtime(now);
		ss << "crashes/" << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S") << ".crash";
		std::ofstream file(ss.str());
		ss.str("");
		ss << "MSG: " << _ex.what();
		[[likely]] if (file) {
			file << ss.str();
		}
		std::cerr << ss.str();
	}

	void create_fatal_dump(const FatalEngineException& _ex) {
		if (!std::filesystem::is_directory("crashes")) {
			std::filesystem::create_directory("crashes");
		}
		std::stringstream ss;
		const auto now = std::time(nullptr);
		const auto tm = safe_localtime(now);
		ss << "crashes/" << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S") << ".crash";
		std::ofstream file(ss.str());
		ss.str("");
		ss << "MSG: " << _ex.what();
		ss << "File: " << _ex.get_source_line();
		ss << "File: " << _ex.get_source_file();
		[[likely]] if (file) {
			file << ss.str();
		}
		std::cerr << ss.str();
	}
}
