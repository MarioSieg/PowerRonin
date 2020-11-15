// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: main.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#pragma once

#include "../env.hpp"

#if SYS_WINDOWS
#define RONAPI_ENTRY WinMain
#else
#define RONAPI_ENTRY main
#endif
