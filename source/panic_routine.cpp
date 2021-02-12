#include "../Include/PowerRonin/PanicRoutine.hpp"
#include "../Include/PowerRonin/TimeUtils.hpp"
#include "../Include/PowerRonin/MessageBox.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

namespace PowerRonin
{
	void GlobalPanicRoutine(const std::string_view msg, const std::size_t line, const std::string_view file)
	{
		if (!std::filesystem::is_directory("crashes")) [[unlikely]]
		{
			std::filesystem::create_directory("crashes");
		}
		std::stringstream ss;
		const auto now = std::time(nullptr);
		const auto tm = safe_localtime(now);
		ss << "crashes/" << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S") << ".crash";
		std::ofstream fstream(ss.str());
		ss.str("");

		ss << "MSG: " << msg;
		ss << "\nFile: " << line;
		ss << "\nLine: " << file;

		const auto message = ss.str();

		if (fstream) [[likely]]
		{
			fstream << message;
		}

		std::cerr << message;

		ShowMessageBox(msg, "[Panic Routine] Fatal Engine Error!", MessageBoxStyle::Error, MessageBoxButtons::Ok);
		std::terminate();
	}
}
