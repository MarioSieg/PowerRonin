#include "../../Include/PowerRonin/core/Subsystem.hpp"
#include "../../Include/PowerRonin/Xorshift.hpp"

namespace PowerRonin::Core
{
	ISubsystem::ISubsystem(const std::string_view _name
	                       , const std::underlying_type<ServiceEvents::Enum>::type _subscribed_events) noexcept : Name(_name),
	                                                                                                              SubscribedEvents(_subscribed_events), UniqueID(xorshift32()) { }

	auto ISubsystem::PreStartupTime() const noexcept -> double
	{
		return this->preStartupTime;
	}

	auto ISubsystem::PostStartupTime() const noexcept -> double
	{
		return this->postStartupTime;
	}

	auto ISubsystem::PreShutdownTime() const noexcept -> double
	{
		return this->preShutdownTime;
	}

	auto ISubsystem::PostShutdownTime() const noexcept -> double
	{
		return this->postShutdownTime;
	}

	void ISubsystem::OnPreStartup(Runtime&) { }

	void ISubsystem::OnPostStartup(Runtime&) { }

	void ISubsystem::OnPreTick(Runtime&) { }

	void ISubsystem::OnPostTick(Runtime&) { }

	void ISubsystem::OnPreShutdown(Runtime&) { }

	void ISubsystem::OnPostShutdown(Runtime&) { }
} // namespace PowerRonin::Core // namespace PowerRonin::Core
