#include "../include/dce/procinfo.hpp"
#include "../include/dce/env.hpp"

#if SYS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <fstream>
#endif


namespace dce {
	auto get_executable_name() -> std::string {
#if SYS_WINDOWS
		char buf[MAX_PATH];
		GetModuleFileNameA(nullptr, buf, MAX_PATH);
		return buf;
#else /* POSIX */
		std::string sp;
		std::ifstream("/proc/self/comm") >> sp;
		return sp;
#endif
	}

	auto get_process_memory_usage() -> std::size_t {
		return 0;
	}
}
