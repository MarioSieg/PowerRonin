#include "../Include/PowerRonin/Fence.hpp"
#include "../Include/PowerRonin/Platform.hpp"

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
