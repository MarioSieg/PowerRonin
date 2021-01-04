#pragma once

struct GLFWwindow;
struct GLFWmonitor;

namespace power_ronin::platform
{
	extern void center_window(GLFWwindow* const _win, GLFWmonitor* const _monitor);
}
