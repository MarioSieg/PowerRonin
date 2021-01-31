// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#include "../include/power_ronin/interrupt.hpp"
#include "../include/power_ronin/env.hpp"

namespace PowerRonin
{
	void Interrupt()
	{
#if COM_MSVC
		__debugbreak();
#elif CPU_ARM
		asm("bkpt 0");
#elif CPU_X86_64 && (COM_GCC || COM_CLANG)
		asm volatile("int $3");
#else
		int* int3 = reinterpret_cast<int*>(3L);
		*int3 = 3;
#endif
	}
}
