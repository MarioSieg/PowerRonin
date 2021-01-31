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

#include "../../include/power_ronin/core/installer.hpp"

#include "../gui/gui.hpp"
#include "../platform/platform.hpp"
#include "../renderer/renderer.hpp"
#include "../physics/physics.hpp"
#include "../scripting/scripting.hpp"
#include "../audio/audio.hpp"

namespace PowerRonin::Core
{
	void InstallMinimal(Kernel& kernel)
	{
		InstallCommon(kernel);
	}

	void InstallCommon(Kernel& kernel)
	{
		kernel.CreateInstallSubsystem<Scripting::ScriptingSystem>();
		kernel.CreateInstallSubsystem<Platform::PlatformSystem>();
		kernel.CreateInstallSubsystem<Renderer::RenderSystem>();
		kernel.CreateInstallSubsystem<Physics::PhysicsSystem>();
		kernel.CreateInstallSubsystem<Audio::AudioSystem>();
		kernel.CreateInstallSubsystem<Interface::GuiSystem>();
	}
} // namespace PowerRonin::Core // namespace PowerRonin::Core
