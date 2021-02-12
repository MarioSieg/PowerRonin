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
