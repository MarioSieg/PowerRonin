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

#pragma once

#include <string_view>

#define IS_DEBUG false

#ifdef _DEBUG
#undef IS_DEBUG
#define IS_DEBUG true
#endif

/* Contains all supported operating systems. */
enum class System {
	LINUX
	, WINDOWS
	, MAC
};

#define SYS_LINUX false
#define SYS_WINDOWS false
#define SYS_MAC false

/* Contains all supported compiler. */
enum class Compiler {
	/* GNU compiler collection. */
	GCC
	,

	/* Microsoft Visual C++ */
	MSVC
	,

	/* LLVM Clang */
	CLANG
};

/* True if current compiler is GNU compiler collection, else false. */
#define COM_GCC false

/* True if current compiler is microsoft visual C++, else false. */
#define COM_MSVC false

/* True if current compiler is LLVM Clang, else false. */
#define COM_CLANG false

/* Returns the current operating system. For checks use the "SYSTEM" variable! */
[[nodiscard]] constexpr auto determine_system() -> System {
#if defined(__linux__) && !defined(__ANDROID__)
#undef SYS_LINUX
#define SYS_LINUX true
	return System::LINUX;
#elif defined(_WIN64)
#undef SYS_WINDOWS
#define SYS_WINDOWS true
	return System::WINDOWS;
#elif defined(__APPLE__)
#undef SYS_MAC
#define SYS_MAC true
	return System::MAC;
#else
#error "env.hpp: Unknown operating system!"
#endif
}

/* Returns the short name of the current operating system. If you need the name, use the "SYSTEM_NAME" variable! */
[[nodiscard]] constexpr auto determine_system_name() -> std::string_view {
	switch (determine_system()) {
	case System::LINUX: return "Linux";
	case System::WINDOWS: return "Windows";
	case System::MAC: return "Mac";
	default: return "Unknown";
	}
}

/* Returns the current compiler. For checks use the "COMPILER" variable! */
[[nodiscard]] constexpr auto determine_compiler() -> Compiler {
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
	return Compiler::CLANG;
#else
#error "env.hpp: Unknown compiler!"
#endif
}

/* Returns the short name of the current compiler. If you need the name, use the "COMPILER_NAME" variable! */
[[nodiscard]] constexpr auto determine_compiler_name() -> std::string_view {
	switch (determine_compiler()) {
	case Compiler::GCC: return "GCC";
	case Compiler::MSVC: return "MSVC";
	case Compiler::CLANG: return "Clang";
	}
}

/* Is set to the current operating system. */
constexpr auto SYSTEM = determine_system();

/* Is set to the current short operating system name. */
constexpr auto SYSTEM_NAME = determine_system_name();

/* Is set to the current compiler. */
constexpr auto COMPILER = determine_compiler();

/* Is set to the current compiler name. */
constexpr auto COMPILER_NAME = determine_compiler_name();

/* Is set to true if debug mode is enabled. */
constexpr auto DEBUG_MODE = IS_DEBUG;

/* Char used to XOR-encrypt memory address prints. */
constexpr auto MEMORY_KEY = '&';

#define CPU_ARM   false
#define CPU_JIT   false
#define CPU_MIPS  false
#define CPU_PPC   false
#define CPU_RISCV false
#define CPU_X86   false

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
#	undef  CPU_X86
#	define CPU_X86 true
#else
#	undef  CPU_JIT
#	define CPU_JIT true
#endif

#define SIMD_SSE false
#define SIMD_SSE2 false
#define SIMD_SSE3 false
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
#undef SIMD_SEE3
#define SIMD_SEE3 true
#endif

#if __AVX__
#undef SIMD_AVX
#define SIMD_AVX true
#endif


#if __AVX2__
#undef SIMD_AVX2
#define SIMD_AVX2 true
#endif


#if __AVX512__
#undef SIMD_AVX512
#define SIMD_AVX512 true
#endif
