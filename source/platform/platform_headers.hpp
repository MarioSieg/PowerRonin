#pragma once

#include "../../include/power_ronin/env.hpp"
#include "../../extern/infoware/include/infoware/infoware.hpp"

#ifdef GLFW_NATIVE
#if SYS_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#elif SYS_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif SYS_MAC
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#endif

#include "../../extern/glfw/include/GLFW/glfw3.h"
#include "../../extern/glfw/include/GLFW/glfw3native.h"
