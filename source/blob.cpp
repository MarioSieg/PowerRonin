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

#include "../include/dce/blob.hpp"
#include <fstream>

namespace dce {
	auto blob_from_disk(const std::filesystem::path& file) -> Blob {
		std::basic_ifstream<std::byte> stream(file, std::ios::in | std::ios::binary);
		if (!stream) {
			return {};
		}
		return std::vector<std::byte>(std::istreambuf_iterator<std::byte>(stream), std::istreambuf_iterator<std::byte>());
	}
}
