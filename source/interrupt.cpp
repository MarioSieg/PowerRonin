#include "../Include/PowerRonin/Interrupt.hpp"
#include "../Include/PowerRonin/Platform.hpp"

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
