#include "../Include/PowerRonin/ProcessInfo.hpp"
#include "../Include/PowerRonin/Platform.hpp"

#if OS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <fstream>
#endif


namespace PowerRonin
{
	auto ExecutableName() -> std::string
	{
#if OS_WINDOWS
		char buf[MAX_PATH];
		GetModuleFileNameA(nullptr, buf, MAX_PATH);
		return buf;
#else /* POSIX */
		std::string sp;
		std::ifstream("/proc/self/comm") >> sp;
		return sp;
#endif
	}

	auto ProcessMemoryUsage() -> std::size_t
	{
		return 0;
	}
}
