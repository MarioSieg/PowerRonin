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
	constexpr std::string_view DREAMCAST_DLL_NAME = "dreamcast";
	constexpr std::string_view DREAMCAST_DLL_CORE_CLASS_NAMESPACE = "Dreamcast.Core";
	constexpr std::string_view DREAMCAST_DLL_CORE_CLASS = "Core";
	constexpr std::string_view DREAMCAST_DLL_CORE_START = "OnSystemStart";
	constexpr std::string_view DREAMCAST_DLL_CORE_UPDATE = "OnSystemUpdate";
	constexpr std::string_view DREAMCAST_DLL_CORE_EXIT = "OnSystemExit";
}
