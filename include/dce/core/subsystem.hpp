// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: subsystem.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include <cstdint>
#include <limits>
#include <string_view>

namespace dce {
	class State;

	namespace core {
		// Bitmask to subscribe to subsystem events
		struct ServiceEvents {
			enum Enum : std::uint8_t {
				NONE = 0
				, PRE_STARTUP = 1 << 0
				, POST_STARTUP = 1 << 1
				, PRE_TICK = 1 << 2
				, POST_TICK = 1 << 3
				, PRE_SHUTDOWN = 1 << 4
				, POST_SHUTDOWN = 1 << 5
				, ALL = std::numeric_limits<std::uint8_t>::max()
			};
		};

		/* Represents an engine subsystem (base interface) */
		class ISubsystem {
			friend class Kernel;

		protected:
			ISubsystem(std::string_view name, std::underlying_type<ServiceEvents::Enum>::type subscribed_events) noexcept;

		public:
			/* Name of the subsystem */
			const std::string_view name;

			/* Subscribed event for this subsystem */
			const std::underlying_type<ServiceEvents::Enum>::type subscribed_events;

			/* 16-bit short UUID for this subsystem */
			const std::uint_fast16_t id;

			/* Delete copy and move constructor and assignment operators */
			ISubsystem(const ISubsystem&) = delete;
			ISubsystem(ISubsystem&&) = delete;
			auto operator=(const ISubsystem&) -> ISubsystem& = delete;
			auto operator=(ISubsystem&&) -> ISubsystem& = delete;

			/* Virtual destructor */
			virtual ~ISubsystem() = default;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto get_pre_startup_time() const noexcept -> double;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto get_post_startup_time() const noexcept -> double;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto get_pre_tick_time() const noexcept -> double;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto get_post_tick_time() const noexcept -> double;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto get_pre_shutdown_time() const noexcept -> double;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto get_post_shutdown_time() const noexcept -> double;


		protected:
			[[nodiscard]] virtual auto on_pre_startup(State& /*unused*/) -> bool;

			[[nodiscard]] virtual auto on_post_startup(State& /*unused*/) -> bool;

			[[nodiscard]] virtual auto on_pre_tick(State& /*unused*/) -> bool;

			[[nodiscard]] virtual auto on_post_tick(State& /*unused*/) -> bool;

			[[nodiscard]] virtual auto on_pre_shutdown(State& /*unused*/) -> bool;

			[[nodiscard]] virtual auto on_post_shutdown(State& /*unused*/) -> bool;

		private:
			double pre_startup_time = 0.;
			double post_startup_time = 0.;
			double pre_tick_time = 0.;
			double post_tick_time = 0.;
			double pre_shutdown_time = 0.;
			double post_shutdown_time = 0.;
		};
	} // namespace core // namespace core
} // namespace dce // namespace dce
