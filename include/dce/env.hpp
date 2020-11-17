// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: env.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

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
#elif defined(_MSC_VER)
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
