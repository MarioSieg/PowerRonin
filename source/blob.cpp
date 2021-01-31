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

#include "../include/power_ronin/blob.hpp"
#include "../include/power_ronin/env.hpp"
#include "../include/power_ronin/except.hpp"

namespace PowerRonin
{
	void ReadBlobFromDisk(const std::filesystem::path& filePath, Blob& out)
	{
		const auto path = filePath.string();
		FILE* file;
#if COM_MSVC
		fopen_s(&file, path.c_str(), "rb");
#else
		file = fopen(path.c_str(), "rb");
#endif
		if (!file) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Binary blob read failed: " + filePath.string());
		}
		fseek(file, 0, SEEK_END);
		const long size = ftell(file);
		if (!size) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Binary blob read failed: " + filePath.string());
		}
		rewind(file);
		out.resize(size);
		const auto read = fread(out.data(), sizeof(std::byte), size, file);
		if (static_cast<unsigned long long>(size) != read) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Binary blob read failed: " + filePath.string());
		}
	}
}
