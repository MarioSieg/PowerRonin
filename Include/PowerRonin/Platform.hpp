#pragma once

#include <string_view>

#define IS_DEBUG false

#ifdef _DEBUG
#undef IS_DEBUG
#define IS_DEBUG true
#endif

/* Contains all supported operating systems. */
enum class System
{
	Linux,
	Windows,
	Mac
};

#define OS_LINUX false
#define OS_WINDOWS false
#define OS_MAC false

/* Contains all supported compiler. */
enum class Compiler
{
	/* GNU compiler collection. */
	GCC,

	/* Microsoft Visual C++ */
	MSVC,

	/* LLVM Clang */
	Clang
};

/* True if current compiler is GNU compiler collection, else false. */
#define COM_GCC false

/* True if current compiler is microsoft visual C++, else false. */
#define COM_MSVC false

/* True if current compiler is LLVM Clang, else false. */
#define COM_CLANG false

/* Returns the current operating system. For checks use the "SYSTEM" variable! */
[[nodiscard]] constexpr auto DetermineSystem() -> enum System
{
#if defined(__linux__) && !defined(__ANDROID__)
#undef OS_LINUX
#define OS_LINUX true
	return System::Linux;
#elif defined(_WIN64)
#undef OS_WINDOWS
#define OS_WINDOWS true
	return System::Windows;
#elif defined(__APPLE__)
#undef OS_MAC
#define OS_MAC true
	return System::Mac;
#else
#error "env.hpp: Unknown operating system!"
#endif
}

/* Returns the short name of the current operating system. If you need the name, use the "SYSTEM_NAME" variable! */
[[nodiscard]] constexpr auto DetermineSystemName() -> std::string_view
{
	switch (DetermineSystem())
	{
		case System::Linux: return "Linux";
		case System::Windows: return "Windows";
		case System::Mac: return "Mac";
		default: return "Unknown";
	}
}

/* Returns the current compiler. For checks use the "COMPILER" variable! */
[[nodiscard]] constexpr auto DetermineCompiler() -> enum Compiler
{
#ifdef __GNUC__
#undef COM_GCC
#define COM_GCC true
	return Compiler::GCC;
#elif defined(_MSC_VER) &&  !defined(__clang__)
#undef COM_MSVC
#define COM_MSVC true
	return Compiler::MSVC;
#elif defined(__clang__)
#undef COM_CLANG
#define COM_CLANG true
	return Compiler::Clang;
#else
#error "env.hpp: Unknown compiler!"
#endif
}

/* Returns the short name of the current compiler. If you need the name, use the "COMPILER_NAME" variable! */
[[nodiscard]] constexpr auto DetermineCompilerName() -> std::string_view
{
	switch (DetermineCompiler())
	{
		case Compiler::GCC: return "GCC";
		case Compiler::MSVC: return "MSVC";
		case Compiler::Clang: return "Clang";
	}
}

/* Is set to the current operating system. */
constexpr auto System = DetermineSystem();

/* Is set to the current short operating system name. */
constexpr auto SystemName = DetermineSystemName();

/* Is set to the current compiler. */
constexpr auto Compiler = DetermineCompiler();

/* Is set to the current compiler name. */
constexpr auto CompilerName = DetermineCompilerName();

/* Is set to true if debug mode is enabled. */
constexpr auto DebugMode = IS_DEBUG;

/* Char used to XOR-encrypt memory address prints. */
constexpr auto MemoryKey = '&';

#define CPU_ARM			false
#define CPU_JIT			false
#define CPU_MIPS		false
#define CPU_PPC			false
#define CPU_RISCV		false
#define CPU_X86_64		false

#if defined(__arm__)     \
 || defined(__aarch64__) \
 || defined(_M_ARM)
#	undef  CPU_ARM
#	define CPU_ARM true
#elif defined(__MIPSEL__)     \
 ||   defined(__mips_isa_rev) \
 ||   defined(__mips64)
#	undef  CPU_MIPS
#	define CPU_MIPS true
#elif defined(_M_PPC)        \
 ||   defined(__powerpc__)   \
 ||   defined(__powerpc64__)
#	undef  CPU_PPC
#	define CPU_PPC true
#elif defined(__riscv)   \
 ||   defined(__riscv__) \
 ||   defined(RISCVEL)
#	undef  CPU_RISCV
#	define CPU_RISCV true
#elif defined(_M_IX86)    \
 ||   defined(_M_X64)     \
 ||   defined(__i386__)   \
 ||   defined(__x86_64__)
#	undef  CPU_X86_64
#	define CPU_X86_64 true
#else
#	undef  CPU_JIT
#	define CPU_JIT true
#endif

#define SIMD_SSE false
#define SIMD_SSE2 false
#define SIMD_SSE3 false
#define SIMD_SSSE3 false
#define SIMD_SSE4_1 false
#define SIMD_SSE4_2 false
#define SIMD_AVX false
#define SIMD_AVX2 false
#define SIMD_AVX512 false

#if __SSE__
#undef SIMD_SEE
#define SIMD_SEE true
#endif

#if __SSE2__
#undef SIMD_SEE2
#define SIMD_SEE2 true
#endif

#if __SSE3__
#undef SIMD_SSE3
#define SIMD_SSE3 true
#endif

#if __SSSE3__
#undef SIMD_SSSE3
#define SIMD_SSSE3 true
#endif

#if __SSE4_1__
#undef SIMD_SSE4_1
#define SIMD_SSE4_1 true
#endif

#if __SSE4_2__
#undef SIMD_SSE4_2
#define SIMD_SSE4_2 true
#endif

#if __AVX__
#undef SIMD_AVX
#define SIMD_AVX true
#endif


#if __AVX2__
#undef SIMD_AVX2
#define SIMD_AVX2 true
#endif


#if __AVX512F__
#undef SIMD_AVX512
#define SIMD_AVX512 true
#endif
