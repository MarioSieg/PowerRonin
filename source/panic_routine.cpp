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

namespace power_ronin
{
	void global_panic_routine(const std::string_view _msg, const std::size_t _line, const std::string_view _file)
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

		ss << "MSG: " << _msg;
		ss << "\nFile: " << _line;
		ss << "\nLine: " << _file;
		ss << "\nDo you want to send the report to KerboGames?";

		const auto msg = ss.str();

		if (file) [[likely]]
		{
			file << msg;
		}

		std::cerr << msg;

		show_message_box(msg, "[Panic Routine] Fatal Engine Error!", MessageBoxStyle::ERROR, MessageBoxButtons::YES_NO);
	}
}
