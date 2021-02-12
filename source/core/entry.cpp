#include "../../Include/PowerRonin/InterruptHandler.hpp"
#include "../../Include/PowerRonin/PanicRoutine.hpp"

#include "../../Include/PowerRonin/core/Entry.hpp"
#include "../../Include/PowerRonin/core/Kernel.hpp"
#include "../../Include/PowerRonin/core/Installer.hpp"

using namespace PowerRonin;
using namespace Core;

auto PowerRoninEntry(const int argc, const char** const argv, const char** const envp) -> int
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
