// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: entry.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "include/dce/core/kernel.hpp"
#include "include/dce/core/installer.hpp"
#include "include/dce/core/misc.hpp"

using namespace dce::core;

/* Main function where the dream starts and ends. */
auto DREAM_ENTRY(const int _argc, const char* const* const _argv, const char* const* const _envp) -> int {
#if !IS_DEBUG
	try {
#endif
		ScopedVectoredExceptionHandler _ = {};

		auto kernel = Kernel::create(_argc, _argv, _envp);
		kernel->install_subsystems(&install_common);
		kernel->startup();
		kernel->execute();
		kernel->shutdown();
		return 0;
#if !IS_DEBUG
	}
	catch (const dce::FatalEngineException& ex) {
		create_fatal_dump(ex);
		return -1;
	}
	catch (const std::runtime_error& ex) {
		create_fatal_dump(ex);
		return -1;
	}
	catch (...) {
		create_fatal_dump();
		return -1;
	}
#endif
}