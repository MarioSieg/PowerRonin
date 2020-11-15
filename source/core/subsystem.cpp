// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: subsystem.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#include "../../include/dce/core/subsystem.hpp"
#include "../../include/dce/xorshift.hpp"

namespace dce::core {
	ISubsystem::ISubsystem(const std::string_view name
	                       , const std::underlying_type<ServiceEvents::Enum>::type subscribed_events) noexcept :
		name(name), subscribed_events(subscribed_events), id(xorshift32()) { }

	auto ISubsystem::get_pre_startup_time() const noexcept -> double {
		return this->pre_startup_time;
	}

	auto ISubsystem::get_post_startup_time() const noexcept -> double {
		return this->post_startup_time;
	}

	auto ISubsystem::get_pre_tick_time() const noexcept -> double {
		return this->pre_tick_time;
	}

	auto ISubsystem::get_post_tick_time() const noexcept -> double {
		return this->post_tick_time;
	}

	auto ISubsystem::get_pre_shutdown_time() const noexcept -> double {
		return this->pre_shutdown_time;
	}

	auto ISubsystem::get_post_shutdown_time() const noexcept -> double {
		return this->post_shutdown_time;
	}

	auto ISubsystem::on_pre_startup(State & /*unused*/) -> bool {
		return true;
	}

	auto ISubsystem::on_post_startup(State & /*unused*/) -> bool {
		return true;
	}

	auto ISubsystem::on_pre_tick(State & /*unused*/) -> bool {
		return true;
	}

	auto ISubsystem::on_post_tick(State & /*unused*/) -> bool {
		return true;
	}

	auto ISubsystem::on_pre_shutdown(State & /*unused*/) -> bool {
		return true;
	}

	auto ISubsystem::on_post_shutdown(State & /*unused*/) -> bool {
		return true;
	}
} // namespace dce::core // namespace dce::core
