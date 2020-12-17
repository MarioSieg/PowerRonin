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

#pragma once

#include <string_view>

namespace dce::scripting {
	constexpr std::string_view ASSEMBLY_NAME_ID = "dreamcast";
	constexpr std::string_view ASSEMBLY_NAMESPACE_ID = "Dreamcast.Core";

	constexpr std::string_view CORE_CLASS_ID = "Core";
	constexpr std::string_view CORE_START_ID = "OnSystemStart";
	constexpr std::string_view CORE_UPDATE_ID = "OnSystemUpdate";
	constexpr std::string_view CORE_EXIT_ID = "OnSystemExit";

	constexpr std::string_view COMMAND_DB_CLASS_ID = "CommandDB";
	constexpr std::string_view COMMAND_DB_CMD_ENTER_ID = "OnCommandEnter";
	constexpr std::uint8_t COMMAND_DB_CMD_ENTER_PARAMS = 1;
}
