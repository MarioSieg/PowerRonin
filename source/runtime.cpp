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

#include "../include/power_ronin/runtime.hpp"

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
