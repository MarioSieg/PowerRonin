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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../include/dce/interrupt.hpp"
#include "../include/dce/env.hpp"

namespace dce {
	void interrupt() {
#if COM_MSVC
		__debugbreak();
#elif CPU_ARM
		asm("bkpt 0");
#elif CPU_X86 && (COM_GCC || COM_CLANG)
		asm volatile("int $3");
#else
		int* int3 = reinterpret_cast<int*>(3L);
		*int3 = 3;
#endif
	}
}
