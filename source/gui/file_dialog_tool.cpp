#if AUTO_TEC

#include "file_dialog_tool.hpp"
#include "../../extern/nativefiledialog/src/include/nfd.h"
#include <cstddef>

namespace PowerRonin::Interface
{
	void open_file_dialog(char*& _out, const char* const _filter, const char* const _default_path)
	{
		nfdchar_t* path = nullptr;
		const nfdresult_t result = NFD_OpenDialog(_filter, _default_path, &path);
		_out = result == NFD_OKAY && path ? path : nullptr;
	}

	void open_files_dialog(void (&_callback)(const char*), const char* const _filter, const char* const _default_path)
	{
		nfdpathset_t* paths = nullptr;
		const nfdresult_t result = NFD_OpenDialogMultiple(_filter, _default_path, paths);
		if (result != NFD_OKAY || paths && !paths->count) [[unlikely]]
		{
			if (paths) [[unlikely]]
			{
				NFD_PathSet_Free(paths);
			}
			return;
		}
		for (std::size_t i = 0; i < NFD_PathSet_GetCount(paths); ++i)
		{
			const auto* const path = NFD_PathSet_GetPath(paths, i);
			if (path) [[likely]]
			{
				_callback(path);
			}
		}
	}

	void save_file_dialog(char*& _out, const char* const _filter, const char* const _default_path)
	{
		nfdchar_t* path = nullptr;
		const nfdresult_t result = NFD_SaveDialog(_filter, _default_path, &path);
		_out = result == NFD_OKAY && path ? path : nullptr;
	}
}

#endif
