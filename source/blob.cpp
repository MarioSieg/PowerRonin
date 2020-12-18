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
#include "../include/dce/except.hpp"

namespace dce {
	void blob_from_disk(const std::filesystem::path& _file, Blob& _blob) {
		const auto path = _file.string();
		FILE* file;
#if COM_MSVC
		fopen_s(&file, path.c_str(), "rb");
#else
		file = fopen(_file.string().data(), "rb");
#endif
		[[unlikely]] if (!file) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Binary blob read failed!");
		}
		fseek(file, 0, SEEK_END);
		const long size = ftell(file);
		[[unlikely]] if (!size) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Binary blob read failed!");
		}
		rewind(file);
		_blob.resize(size);
		const auto read = fread(_blob.data(), sizeof(std::byte), size, file);
		[[unlikely]] if (static_cast<unsigned long long>(size) != read) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Binary blob read failed!");
		}
	}
}
