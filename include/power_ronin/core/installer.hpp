#pragma once

namespace power_ronin::core
{
	class Kernel;

	extern auto install_minimal(Kernel& _kernel) -> bool;
	extern auto install_common(Kernel& _kernel) -> bool;
} // namespace power_ronin::core
