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

using namespace PowerRonin;
using namespace Core;

auto PowerRoninEntry(const int argc, const char** const  argv, const char** const envp) -> int
{
#if !IS_DEBUG
	try
	{
#endif
		ScopedVectoredExceptionHandler breakpointHandler = {};

		auto kernel = Kernel::Create(argc, argv, envp);
		kernel->InstallSubsystems(&InstallCommon);
		kernel->Startup();
		kernel->Execute();
		kernel->Shutdown();
		return 0;
#if !IS_DEBUG
	}
	catch (const FatalEngineException& ex)
	{
		GlobalPanicRoutine(ex.what(), ex.source_line(), ex.source_file());
	}
	catch (const std::runtime_error& ex)
	{
		GlobalPanicRoutine(ex.what());
	}
	catch (...)
	{
		GlobalPanicRoutine("Unknown error!");
	}
#endif
}
