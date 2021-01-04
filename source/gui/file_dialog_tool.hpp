#pragma once

namespace power_ronin::gui
{
	extern void open_file_dialog(char*& _out, const char* _filter = nullptr, const char* _default_path = nullptr);

	extern void open_files_dialog(void (&_callback)(const char*)
	                              , const char* _filter = nullptr
	                              , const char* _default_path = nullptr);

	extern void save_file_dialog(char*& _out, const char* _filter = nullptr, const char* _default_path = nullptr);
}
