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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../../include/dce/core/subsystem.hpp"
#include "../../include/dce/xorshift.hpp"

namespace dce::core {
	ISubsystem::ISubsystem(const std::string_view _name, const std::underlying_type<ServiceEvents::Enum>::type _subscribed_events) noexcept : name(_name), subscribed_events(_subscribed_events), id(xorshift32()) { }

	auto ISubsystem::get_pre_startup_time() const noexcept -> double {
		return this->pre_startup_time_;
	}

	auto ISubsystem::get_post_startup_time() const noexcept -> double {
		return this->post_startup_time_;
	}

	auto ISubsystem::get_pre_tick_time() const noexcept -> double {
		return this->pre_tick_time_;
	}

	auto ISubsystem::get_post_tick_time() const noexcept -> double {
		return this->post_tick_time_;
	}

	auto ISubsystem::get_pre_shutdown_time() const noexcept -> double {
		return this->pre_shutdown_time_;
	}

	auto ISubsystem::get_post_shutdown_time() const noexcept -> double {
		return this->post_shutdown_time_;
	}

	auto ISubsystem::on_pre_startup(Runtime& /*unused*/) -> bool {
		return true;
	}

	auto ISubsystem::on_post_startup(Runtime& /*unused*/) -> bool {
		return true;
	}

	auto ISubsystem::on_pre_tick(Runtime& /*unused*/) -> bool {
		return true;
	}

	auto ISubsystem::on_post_tick(Runtime& /*unused*/) -> bool {
		return true;
	}

	auto ISubsystem::on_pre_shutdown(Runtime& /*unused*/) -> bool {
		return true;
	}

	auto ISubsystem::on_post_shutdown(Runtime& /*unused*/) -> bool {
		return true;
	}
} // namespace dce::core // namespace dce::core
