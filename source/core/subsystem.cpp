// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#include "../../include/power_ronin/core/subsystem.hpp"
#include "../../include/power_ronin/xorshift.hpp"

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

	void ISubsystem::OnPreStartup(Runtime&)
	{

	}

	void ISubsystem::OnPostStartup(Runtime&)
	{

	}

	void ISubsystem::OnPreTick(Runtime&)
	{

	}

	void ISubsystem::OnPostTick(Runtime&)
	{

	}

	void ISubsystem::OnPreShutdown(Runtime&)
	{

	}

	void ISubsystem::OnPostShutdown(Runtime&)
	{

	}
} // namespace PowerRonin::Core // namespace PowerRonin::Core
