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

#include "util.hpp"
#include "platform_headers.hpp"

namespace PowerRonin::Platform
{
	void center_window(GLFWwindow* const _win, GLFWmonitor* const _monitor)
	{
		if (!_monitor || !_win) [[unlikely]]
		{
			return;
		}

		const auto* const video_mode = glfwGetVideoMode(_monitor);
		if (!video_mode) [[unlikely]]
		{
			return;
		}

		int mx, my;
		glfwGetMonitorPos(_monitor, &mx, &my);

		int ww, wh;
		glfwGetWindowSize(_win, &ww, &wh);

		glfwSetWindowPos(_win, mx + (video_mode->width - ww) / 2, my + (video_mode->height - wh) / 2);
	}
}
