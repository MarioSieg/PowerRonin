// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#include "../include/power_ronin/panic_routine.hpp"
#include "../include/power_ronin/time_utils.hpp"
#include "../include/power_ronin/msgbox.hpp"

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
