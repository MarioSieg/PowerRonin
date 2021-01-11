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

#if AUTO_TEC

#pragma once

namespace power_ronin::gui
{
	extern void open_file_dialog(char*& _out, const char* _filter = nullptr, const char* _default_path = nullptr);

	extern void open_files_dialog(void (&_callback)(const char*)
	                              , const char* _filter = nullptr
	                              , const char* _default_path = nullptr);

	extern void save_file_dialog(char*& _out, const char* _filter = nullptr, const char* _default_path = nullptr);
}

#endif
