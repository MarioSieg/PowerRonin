#include "core.hpp"

namespace PowerRonin::Core
{
	void Kernel::Core::PrintSubsystemInfo()
	{
		std::size_t i = 0;
		auto& proto = this->Runtime->Protocol();
		for (const auto& system : this->Subsystems)
		{
			const auto id = std::get<0>(system);
			const auto& sys = std::get<1>(system);
			const auto* const name = typeid(decltype(*sys)).name();
			const auto hash = typeid(decltype(*sys)).hash_code();

			proto.Info("Found installed subsystem {} of {}:", ++i, this->Subsystems.size());
			proto.Info("\tID: {:#x}", id);
			proto.Info("\tTypename: {}", name);
			proto.Info("\tHash: {:#x}", hash);
			proto.Info("\tName: {}", sys->Name);
			proto.Info("\tMask: {:#08b}", sys->SubscribedEvents);
		}
	}

	void Kernel::Core::DispatchPreStartup()
	{
		for (auto sys = this->Subsystems.begin(); sys != this->Subsystems.end(); std::advance(sys, 1))
		{
			const auto& name = std::get<1>(*sys)->Name;
			this->Runtime->Protocol().Critical(R"(Invoking kernel event "on_pre_startup" on subsystem interface "{}"...)", name);
			const auto tik2 = std::chrono::high_resolution_clock::now();
			if (std::get<1>(*sys)->SubscribedEvents & ServiceEvents::PreStartup) [[likely]]
			{
				std::get<1>(*sys)->OnPreStartup(*this->Runtime);
			}
			const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			this->Runtime->Protocol().Info("OK! \"on_pre_startup\" invoked! {}s elapsed!", std::get<1>(*sys)->preStartupTime = dur);
		}
	}
	
	void Kernel::Core::DispatchPostStartup()
	{
		for (auto sys = this->Subsystems.rbegin(); sys != this->Subsystems.rend(); std::advance(sys, 1))
		{
			const auto& name = std::get<1>(*sys)->Name;
			this->Runtime->Protocol().Critical(R"(Invoking kernel event "on_post_startup" on subsystem interface "{}"...)", name);
			const auto tik2 = std::chrono::high_resolution_clock::now();
			if (std::get<1>(*sys)->SubscribedEvents & ServiceEvents::PostStartup) [[likely]]
			{
				std::get<1>(*sys)->OnPostStartup(*this->Runtime);
			}
			const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			this->Runtime->Protocol().Info("OK! \"on_post_startup\" invoked! {}s elapsed!", std::get<1>(*sys)->postStartupTime = dur);
		}
	}
	
	void Kernel::Core::DispatchPreTick()
	{
		for (auto sys = this->Subsystems.begin(); sys != this->Subsystems.end(); std::advance(sys, 1))
		{
			if (std::get<1>(*sys)->SubscribedEvents & ServiceEvents::PreTick) [[likely]]
			{
				std::get<1>(*sys)->OnPreTick(*this->Runtime);
			}
		}
	}
	
	void Kernel::Core::DispatchPostTick()
	{
		for (auto sys = this->Subsystems.rbegin(); sys != this->Subsystems.rend(); std::advance(sys, 1))
		{
			if (std::get<1>(*sys)->SubscribedEvents & ServiceEvents::PostTick) [[unlikely]]
			{
				std::get<1>(*sys)->OnPostTick(*this->Runtime);
			}
		}
	}
	
	void Kernel::Core::DispatchPreShutdown()
	{
		for (auto sys = this->Subsystems.begin(); sys != this->Subsystems.end(); ++sys)
		{
			const auto tik2 = std::chrono::high_resolution_clock::now();
			const auto& name = std::get<1>(*sys)->Name;
			if (std::get<1>(*sys)->SubscribedEvents & ServiceEvents::PreShutdown) [[likely]]
			{
				std::get<1>(*sys)->OnPreShutdown(*this->Runtime);
			}
			const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			std::get<1>(*sys)->preShutdownTime = dur;
		}
	}
	
	void Kernel::Core::DispatchPostShutdown()
	{
		for (auto sys = this->Subsystems.rbegin(); sys != this->Subsystems.rend(); ++sys)
		{
			const auto tik2 = std::chrono::high_resolution_clock::now();
			const auto& name = std::get<1>(*sys)->Name;
			if (std::get<1>(*sys)->SubscribedEvents & ServiceEvents::PostShutdown) [[unlikely]]
			{
				std::get<1>(*sys)->OnPostShutdown(*this->Runtime);
			}
			const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			std::get<1>(*sys)->postShutdownTime = dur;
		}
	}
}
