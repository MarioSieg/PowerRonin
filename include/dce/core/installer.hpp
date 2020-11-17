// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: installer.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

namespace dce::core {
	class Kernel;

	extern auto install_minimal(Kernel &_kernel) -> bool;
	extern auto install_common(Kernel &_kernel) -> bool;
} // namespace dce::core
