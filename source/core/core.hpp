#pragma once

#include "../../Include/PowerRonin/core/Kernel.hpp"

namespace PowerRonin::Core
{
	enum class KernelState : std::int_fast32_t
	{
		Offline = 0,
		Online = 1,
		Running = -1
	};

	struct Kernel::Core final
	{
		KernelState KernelState = KernelState::Offline;
		std::vector<std::tuple<std::uint_fast16_t, std::unique_ptr<ISubsystem>>> Subsystems = {};
		std::unique_ptr<class Runtime> Runtime = nullptr;

		void PrintSubsystemInfo();
		void DispatchPreStartup();
		void DispatchPostStartup();
		void DispatchPreTick();
		void DispatchPostTick();
		void DispatchPreShutdown();
		void DispatchPostShutdown();
	};
}
