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

#include "file_dialog_tool.hpp"
#include "../../extern/nativefiledialog/src/include/nfd.h"
#include <cstddef>

namespace dce::gui {
	void open_file_dialog(char*& _out, const char* const _filter, const char* const _default_path) {
		nfdchar_t* path = nullptr;
		const nfdresult_t result = NFD_OpenDialog(_filter, _default_path, &path);
		_out = result == NFD_OKAY && path ? path : nullptr;
	}

	void open_files_dialog(void (&_callback)(const char*), const char* const _filter, const char* const _default_path) {
		nfdpathset_t* paths = nullptr;
		const nfdresult_t result = NFD_OpenDialogMultiple(_filter, _default_path, paths);
		[[unlikely]] if (result != NFD_OKAY || paths && !paths->count) {
			[[unlikely]] if (paths) {
				NFD_PathSet_Free(paths);
			}
			return;
		}
		for (std::size_t i = 0; i < NFD_PathSet_GetCount(paths); ++i) {
			const auto* const path = NFD_PathSet_GetPath(paths, i);
			[[likely]] if (path) {
				_callback(path);
			}
		}
	}

	void save_file_dialog(char*& _out, const char* const _filter, const char* const _default_path) {
		nfdchar_t* path = nullptr;
		const nfdresult_t result = NFD_SaveDialog(_filter, _default_path, &path);
		_out = result == NFD_OKAY && path ? path : nullptr;
	}
}
