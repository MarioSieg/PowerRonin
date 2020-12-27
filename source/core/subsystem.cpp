#include "../../include/dce/core/subsystem.hpp"
#include "../../include/dce/xorshift.hpp"

namespace dce::core {
	ISubsystem::ISubsystem(const std::string_view _name
	                       , const std::underlying_type<ServiceEvents::Enum>::type _subscribed_events) noexcept : name(_name),
		subscribed_events(_subscribed_events), id(xorshift32()) {
	}

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
