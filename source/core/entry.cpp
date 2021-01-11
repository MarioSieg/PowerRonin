// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#include "../../include/power_ronin/break_interrupt_handler.hpp"
#include "../../include/power_ronin/panic_routine.hpp"

#include "../../include/power_ronin/core/entry.hpp"
#include "../../include/power_ronin/core/kernel.hpp"
#include "../../include/power_ronin/core/installer.hpp"

using namespace power_ronin;
using namespace core;

auto default_power_ronin_entry(int _argc, const char** _argv, const char** _envp) -> int
{
#if !IS_DEBUG
	try
	{
#endif
		ScopedVectoredExceptionHandler breakpoint_handler = {};

		auto kernel = Kernel::create(_argc, _argv, _envp);
		kernel->install_subsystems(&install_common);
		kernel->startup();
		kernel->execute();
		kernel->shutdown();
		return 0;
#if !IS_DEBUG
	}
	catch (const FatalEngineException& ex)
	{
		global_panic_routine(ex.what(), ex.source_line(), ex.source_file());
		std::terminate();
	}
	catch (const std::runtime_error& ex)
	{
		global_panic_routine(ex.what());
		std::terminate();
	}
	catch (...)
	{
		global_panic_routine("Unknown error!");
		std::terminate();
	}
#endif
}
