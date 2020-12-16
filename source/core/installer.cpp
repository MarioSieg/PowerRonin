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

#include "../../include/dce/core/installer.hpp"

#include "../gui/gui.hpp"
#include "../platform/platform.hpp"
#include "../renderer/renderer.hpp"
#include "../physics/physics.hpp"
#include "../scripting/scripting.hpp"
#include "../audio/audio.hpp"

namespace dce::core {
	auto install_minimal(Kernel& _kernel) -> bool {
		return install_common(_kernel);
	}

	auto install_common(Kernel& _kernel) -> bool {
		_kernel.create_install_subsystem<platform::Platform>();
		_kernel.create_install_subsystem<renderer::Renderer>();
		_kernel.create_install_subsystem<scripting::Scripting>();
		_kernel.create_install_subsystem<physics::Physics>();
		_kernel.create_install_subsystem<audio::Audio>();
		_kernel.create_install_subsystem<gui::Gui>();
		return true;
	}
} // namespace dce::core // namespace dce::core
