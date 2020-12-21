#pragma once

#include "../env.hpp"

#if SYS_WINDOWS
#define DREAM_ENTRY WinMain /* On Windows we need WinMain */
#else
#define DREAM_ENTRY main
#endif
