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

#include <string>
#include <cstddef>

namespace dce {
	/// <summary>
	/// Returns the name of the executable.
	/// </summary>
	[[nodiscard]] extern auto get_executable_name() -> std::string;

	/// <summary>
	///
	/// </summary>
	/// <returns>The amount of RAM memory used by the process in bytes.</returns>
	[[nodiscard]] extern auto get_process_memory_usage() -> std::size_t;
}
