// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: file_dialog_tool.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 12.11.2020 21:20

#pragma once

#include <string_view>

namespace dce::gui {
	extern void open_file_dialog(char *&_out, const char *const _filter = nullptr, const char *const _default_path = nullptr);

	extern void open_files_dialog(void (&_callback)(const char *const), const char *const _filter = nullptr
	                              , const char *const _default_path = nullptr);

	extern void save_file_dialog(char *&_out, const char *const _filter = nullptr, const char *const _default_path = nullptr);
}
