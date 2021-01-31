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

#include "../include/power_ronin/fence.hpp"
#include "../include/power_ronin/env.hpp"

#if COM_MSVC
extern "C" void _ReadBarrier();
#pragma intrinsic(_ReadBarrier)

extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

#if CPU_X86
#include <intrin.h>
#else
#include <winnt.h>
#endif
#else
#define MEM_BARRIER() asm volatile("":::"memory");
#endif

namespace PowerRonin
{
	void ReadFence() noexcept
	{
#if COM_MSVC
		_ReadBarrier();
#else
		MEM_BARRIER()
#endif
	}

	void WriteFence() noexcept
	{
#if COM_MSVC
		_WriteBarrier();
#else
		MEM_BARRIER()
#endif
	}

	void ReadWriteFence() noexcept
	{
#if COM_MSVC
		_ReadWriteBarrier();
#else
		MEM_BARRIER()
#endif
	}

	void MemoryFence() noexcept
	{
#if COM_MSVC
#if CPU_X86
		_mm_mfence();
#else
		MemoryBarrier();
#endif
#else
		__sync_synchronize();
#endif
	}
}
