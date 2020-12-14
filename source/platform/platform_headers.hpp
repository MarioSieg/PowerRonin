// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

#include "../../include/dce/env.hpp"
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
