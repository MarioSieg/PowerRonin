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

#include <filesystem>
#include <vector>

namespace PowerRonin
{
	/// <summary>
	/// Represents a binary large object. (Byte array buffer).
	/// </summary>
	using Blob = std::vector<std::byte>;

	/// <summary>
	/// Loads a blob from a file.
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	extern void ReadBlobFromDisk(const std::filesystem::path& filePath, Blob& out);
}
