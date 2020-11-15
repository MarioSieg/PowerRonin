/* 26.10.2020 */

#include "include/dce/core/kernel.hpp"
#include "include/dce/core/installer.hpp"
#include "include/dce/core/main.hpp"

#include <filesystem>
#include <iostream>

using namespace dce::core;

/* Main function where the simulation starts and ends. */
/* If the compiler/platform does not support "envp", just pass nullptr! */
auto RONAPI_ENTRY(const int argc, const char* const* const argv, const char* const* const envp) -> int {

	std::filesystem::current_path("../../../");
	
	auto kernel = Kernel::create(argc, argv, envp);
	if (!kernel) {
		std::cerr << "Failed to create engine kernel!" << std::endl;
		return -1;
	}

	bool result;
	result = std::get<0>(kernel->install_subsystems(&install_common));
	if (!result) {
		std::cerr << "Failed to install subsystems!" << std::endl;
		return -1;
	}

	result = std::get<0>(kernel->startup());
	if (!result) {
		std::cerr << "Failed to startup engine!" << std::endl;
		return -1;
	}

	result = std::get<0>(kernel->execute());
	if (!result) {
		std::cerr << "Failed to execute engine!" << std::endl;
		return -1;
	}

	result = std::get<0>(kernel->execute());
	if (!result) {
		std::cerr << "Failed to shutdown engine!" << std::endl;
		return -1;
	}

	return 0;
}
