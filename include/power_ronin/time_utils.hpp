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

#include <ctime>
#include <string>

namespace PowerRonin
{
	/// <summary>
	/// Safe alternative for std::localtime
	/// </summary>
	/// <param name="_time"></param>
	/// <returns></returns>
	[[nodiscard]] extern auto safe_localtime(const std::time_t& _time) -> std::tm;

	/// <summary>
	/// Returns safe_localtime as timestamp string.
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] extern auto time_stamp() -> std::string;

	/// <summary>
	/// Writes safe_localtime as timestamp string into a fixed buffer.
	/// </summary>
	/// <param name="_buffer"></param>
	extern void time_stamp(char (&_buffer)[32]);
}
