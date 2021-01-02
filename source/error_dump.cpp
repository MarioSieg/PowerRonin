#include "../include/dce/error_dump.hpp"
#include "../include/dce/except.hpp"
#include "../include/dce/time_utils.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

namespace dce
{
	void create_fatal_dump()
	{
		if (!std::filesystem::is_directory("crashes")) [[unlikely]]
		{
			std::filesystem::create_directory("crashes");
		}
		std::stringstream ss;
		const auto now = std::time(nullptr);
		const auto tm = safe_localtime(now);
		ss << "crashes/" << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S") << ".crash";
		std::ofstream file(ss.str());
		ss.str("");
		ss << "MSG: Fatal unknown error!";
		if (file) [[likely]]
		{
			file << ss.str();
		}
		std::cerr << ss.str();
	}

	void create_fatal_dump(const std::exception& _ex)
	{
		if (!std::filesystem::is_directory("crashes")) [[unlikely]]
		{
			std::filesystem::create_directory("crashes");
		}
		std::stringstream ss;
		const auto now = std::time(nullptr);
		const auto tm = safe_localtime(now);
		ss << "crashes/" << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S") << ".crash";
		std::ofstream file(ss.str());
		ss.str("");
		ss << "MSG: " << _ex.what();
		if (file) [[likely]]
		{
			file << ss.str();
		}
		std::cerr << ss.str();
	}

	void create_fatal_dump(const FatalEngineException& _ex)
	{
		if (!std::filesystem::is_directory("crashes")) [[unlikely]]
		{
			std::filesystem::create_directory("crashes");
		}
		std::stringstream ss;
		const auto now = std::time(nullptr);
		const auto tm = safe_localtime(now);
		ss << "crashes/" << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S") << ".crash";
		std::ofstream file(ss.str());
		ss.str("");
		ss << "MSG: " << _ex.what();
		ss << "\nFile: " << _ex.source_file();
		ss << "\nLine: " << _ex.source_line();
		if (file) [[likely]]
		{
			file << ss.str();
		}
		std::cerr << ss.str();
	}
}
