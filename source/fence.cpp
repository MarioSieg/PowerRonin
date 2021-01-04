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

namespace power_ronin
{
	void read_fence() noexcept
	{
#if COM_MSVC
		_ReadBarrier();
#else
		MEM_BARRIER()
#endif
	}

	void write_fence() noexcept
	{
#if COM_MSVC
		_WriteBarrier();
#else
		MEM_BARRIER()
#endif
	}

	void read_write_fence() noexcept
	{
#if COM_MSVC
		_ReadWriteBarrier();
#else
		MEM_BARRIER()
#endif
	}

	void memory_fence() noexcept
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
