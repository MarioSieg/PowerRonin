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
#include "../include/dce/env.hpp"

namespace dce {
	auto blob_from_disk(const std::filesystem::path& _file) -> Blob {
		const auto path = _file.string();
		FILE* file;
#if COM_MSVC
		fopen_s(&file, path.c_str(), "rb");
#else
		file = fopen(_file.data(), "rb");
#endif
		[[unlikely]] if (!file) {
			return {};
		}
		fseek(file, 0, SEEK_END);
		const long size = ftell(file);
		[[unlikely]] if (!size) {
			return {};
		}
		rewind(file);
		Blob blob = {};
		blob.resize(size);
		const auto read = fread(blob.data(), sizeof(std::byte), size, file);
		blob.resize(read);

		return blob;
	}
}
