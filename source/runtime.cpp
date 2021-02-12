#include "../Include/PowerRonin/Runtime.hpp"

namespace PowerRonin
{
	Runtime::Runtime() : protocol("native"),
	                     scriptingProtocol("managed"),
	                     config(),
	                     resourceManager(this->protocol),
	                     diagnostics(),
	                     chrono(),
	                     scenery(),
	                     input(),
	                     renderData(),
	                     terminalHook(nullptr) { }

	void Runtime::Initialize()
	{
		this->resourceManager.SystemResources.LoadAll(this->resourceManager);
		this->scenery.initialize();
		this->scenery.new_default(this->resourceManager);
	}

	void Runtime::Shutdown()
	{
		this->scenery.unload_all_entities();
		this->resourceManager.UnloadAllResources();
		this->protocol.GetLogger()->flush();
		this->scriptingProtocol.GetLogger()->flush();
	}
}
