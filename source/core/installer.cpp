#include "../../include/power_ronin/core/installer.hpp"

#include "../gui/gui.hpp"
#include "../platform/platform.hpp"
#include "../renderer/renderer.hpp"
#include "../physics/physics.hpp"
#include "../scripting/scripting.hpp"
#include "../audio/audio.hpp"

namespace power_ronin::core
{
	auto install_minimal(Kernel& _kernel) -> bool
	{
		return install_common(_kernel);
	}

	auto install_common(Kernel& _kernel) -> bool
	{
		_kernel.create_install_subsystem<scripting::Scripting>();
		_kernel.create_install_subsystem<platform::Platform>();
		_kernel.create_install_subsystem<renderer::Renderer>();
		_kernel.create_install_subsystem<physics::Physics>();
		_kernel.create_install_subsystem<audio::Audio>();
		_kernel.create_install_subsystem<gui::Gui>();
		return true;
	}
} // namespace power_ronin::core // namespace power_ronin::core
