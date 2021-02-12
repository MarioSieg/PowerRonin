#pragma once

struct GLFWwindow;
struct GLFWmonitor;

namespace PowerRonin::Platform
{
	extern void center_window(GLFWwindow* const _win, GLFWmonitor* const _monitor);
}
