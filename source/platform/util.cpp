#include "util.hpp"
#include "platform_headers.hpp"

namespace dce::platform {

	void center_window(GLFWwindow* const _win, GLFWmonitor* const _monitor) {
		[[unlikely]] if (!_monitor || !_win) {
			return;
		}

		const auto* const video_mode = glfwGetVideoMode(_monitor);
		[[unlikely]] if (!video_mode) {
			return;
		}

		int mx, my;
		glfwGetMonitorPos(_monitor, &mx, &my);

		int ww, wh;
		glfwGetWindowSize(_win, &ww, &wh);

		glfwSetWindowPos(_win, mx + (video_mode->width - ww) / 2, my + (video_mode->height - wh) / 2);
	}
}
