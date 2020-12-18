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

#include "../include/dce/fence.hpp"
#include "../include/dce/env.hpp"

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

#endif

#define MEM_BARRIER() asm volatile("":::"memory")

namespace dce {

	void read_fence() noexcept {
#if COM_MSVC
		_ReadBarrier();
#else
		MEM_BARRIER();
#endif
	}

	void write_fence() noexcept {
#if COM_MSVC
		_WriteBarrier();
#else
		MEM_BARRIER();
#endif
	}

	void read_write_fence() noexcept {
#if COM_MSVC
		_ReadWriteBarrier();
#else
		MEM_BARRIER();
#endif
	}

	void memory_fence() noexcept {
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
