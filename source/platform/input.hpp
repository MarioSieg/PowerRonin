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

struct GLFWcursor;

namespace PowerRonin::Platform
{
	class GuiInput final
	{
	public:
		auto initialize() -> bool;
		void update();
		void shutdown();
		void update_mouse();
		void update_cursor();
		void update_gamepads();
		void install_callback_procedures() const;

	private:
		bool mouse_buttons[5] = {};
		GLFWcursor* cursors[9] = {};
		double timer = .0;
		void* window = nullptr;
	};
} // namespace PowerRonin::platform // namespace PowerRonin::platform
