#include "sysclock.hpp"
#include "../include/dce/env.hpp"

#if SYS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <sys/time.h>
#endif

namespace dce {
	auto get_high_precision_counter() noexcept -> std::uint64_t {
#if SYS_WINDOWS
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return static_cast<std::uint64_t>(li.QuadPart);
#else
	  struct timeval now;
	  gettimeofday(&now, 0);
	  return now.tv_sec * UINT64_C(1000000) + now.tv_usec;
#endif
	}

	auto get_high_precision_frequency() noexcept -> std::uint64_t {
#if SYS_WINDOWS
		LARGE_INTEGER li;
		QueryPerformanceFrequency(&li);
		return li.QuadPart;
#else
	  return UINT64_C(1000000);
#endif
	}
}
