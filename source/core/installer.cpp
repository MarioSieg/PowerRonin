// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: installer.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#include "../../include/dce/core/installer.hpp"
#include "../gui/gui.hpp"
#include "../platform/platform.hpp"
#include "../renderer/renderer.hpp"

namespace dce::core {
	auto install_minimal(Kernel &kernel) -> bool {
		return install_common(kernel);
	}

	auto install_common(Kernel &kernel) -> bool {
		try {
			kernel.create_install_subsystem<platform::Platform>();
			kernel.create_install_subsystem<renderer::Renderer>();
			kernel.create_install_subsystem<gui::Gui>();

			return true;
		}
		catch (...) {
			return false;
		}
	}
} // namespace dce::core // namespace dce::core
