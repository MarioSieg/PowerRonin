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

#pragma once

#include <string_view>

namespace power_ronin::scripting
{
	constexpr std::string_view ASSEMBLY_NAME_ID = "power_ronin";
	constexpr std::string_view ASSEMBLY_NAMESPACE_ID = "PowerRonin.Core";

	constexpr std::string_view CORE_CLASS_ID = "Core";

	constexpr std::string_view CORE_ON_PRE_STARTUP_ID = "OnPreStartup";
	constexpr std::string_view CORE_ON_POST_STARTUP_ID = "OnPostStartup";

	constexpr std::string_view CORE_ON_PRE_TICK_ID = "OnPreTick";
	constexpr std::string_view CORE_ON_POST_TICK_ID = "OnPostTick";

	constexpr std::string_view CORE_PRE_SHUTDOWN_ID = "OnPreShutdown";
	constexpr std::string_view CORE_POST_SHUTDOWN_ID = "OnPostShutdown";

	constexpr std::string_view COMMAND_DB_CLASS_ID = "CommandDB";
	constexpr std::string_view COMMAND_DB_CMD_ENTER_ID = "OnCommandEnter";
	constexpr std::uint8_t COMMAND_DB_CMD_ENTER_PARAMS = 1;
}
