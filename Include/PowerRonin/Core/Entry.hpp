#pragma once

#include "../Platform.hpp"

#if OS_WINDOWS
#define POWER_RONIN_ENTRY WinMain /* On Windows we need WinMain */
#else
#define DREAM_ENTRY main
#endif

extern auto PowerRoninEntry(int argc, const char** argv, const char** envp = nullptr) -> int;
