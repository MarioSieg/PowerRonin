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

#include "../include/dce/error_dump.hpp"
#include "../include/dce/except.hpp"
#include "../include/dce/time_utils.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

namespace dce {
	void create_fatal_dump() {
		[[unlikely]] if (!std::filesystem::is_directory("crashes")) {
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
		[[unlikely]] if (!std::filesystem::is_directory("crashes")) {
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
		[[unlikely]] if (!std::filesystem::is_directory("crashes")) {
			std::filesystem::create_directory("crashes");
		}
		std::stringstream ss;
		const auto now = std::time(nullptr);
		const auto tm = safe_localtime(now);
		ss << "crashes/" << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S") << ".crash";
		std::ofstream file(ss.str());
		ss.str("");
		ss << "MSG: " << _ex.what();
		ss << "\nFile: " << _ex.get_source_file();
		ss << "\nLine: " << _ex.get_source_line();
		[[likely]] if (file) {
			file << ss.str();
		}
		std::cerr << ss.str();
	}
}
