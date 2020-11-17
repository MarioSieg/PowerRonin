// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: installer.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "../../include/dce/core/installer.hpp"

#include "../gui/gui.hpp"
#include "../platform/platform.hpp"
#include "../renderer/renderer.hpp"
#include "../physics/physics.hpp"

namespace dce::core {
	auto install_minimal(Kernel &_kernel) -> bool {
		return install_common(_kernel);
	}

	auto install_common(Kernel &_kernel) -> bool {
		_kernel.create_install_subsystem<platform::Platform>();
		_kernel.create_install_subsystem<renderer::Renderer>();
		_kernel.create_install_subsystem<gui::Gui>();
		_kernel.create_install_subsystem<physics::Physics>();
		return true;
	}
} // namespace dce::core // namespace dce::core
