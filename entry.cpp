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

#include "include/dce/core/kernel.hpp"
#include "include/dce/core/installer.hpp"
#include "include/dce/core/entry.hpp"
#include "include/dce/break_interrupt_handler.hpp"
#include "include/dce/error_dump.hpp"

using namespace dce;
using namespace core;

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
	catch (const FatalEngineException& ex) {
		create_fatal_dump(ex);
		return -1;
	} catch (const std::runtime_error& ex) {
		create_fatal_dump(ex);
		return -1;
	} catch (...) {
		create_fatal_dump();
		return -1;
	}
#endif
}
