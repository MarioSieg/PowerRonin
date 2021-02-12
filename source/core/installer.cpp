#include "../../Include/PowerRonin/core/Installer.hpp"

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
