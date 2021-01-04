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

#pragma once

#include <cstdint>
#include <limits>
#include <string_view>

namespace power_ronin
{
	class Runtime;

	namespace core
	{
		// Bitmask to subscribe to subsystem events
		struct ServiceEvents
		{
			enum Enum : std::uint8_t
			{
				NONE = 0,
				PRE_STARTUP = 1 << 0,
				POST_STARTUP = 1 << 1,
				PRE_TICK = 1 << 2,
				POST_TICK = 1 << 3,
				PRE_SHUTDOWN = 1 << 4,
				POST_SHUTDOWN = 1 << 5,
				ALL = std::numeric_limits<std::uint8_t>::max()
			};
		};

		/* Represents an engine subsystem (base interface) */
		class ISubsystem
		{
			friend class Kernel;

		protected:
			ISubsystem(const std::string_view _name, const std::underlying_type<ServiceEvents::Enum>::type _subscribed_events) noexcept;

		public:
			/* Name of the subsystem */
			const std::string_view name;

			/* Subscribed event for this subsystem */
			const std::underlying_type<ServiceEvents::Enum>::type subscribed_events;

			/* 16-bit short UUID for this subsystem */
			const std::uint_fast16_t id;

			/* Delete copy, move constructors and assignment operators */
			ISubsystem(const ISubsystem&) = delete;
			ISubsystem(ISubsystem&&) = delete;
			auto operator=(const ISubsystem&) -> ISubsystem& = delete;
			auto operator=(ISubsystem&&) -> ISubsystem& = delete;

			/* Virtual destructor */
			virtual ~ISubsystem() = default;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto pre_startup_time() const noexcept -> double;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto post_startup_time() const noexcept -> double;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto pre_shutdown_time() const noexcept -> double;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto post_shutdown_time() const noexcept -> double;


		protected:
			Kernel* kernel_ = nullptr;

			[[nodiscard]] virtual auto on_pre_startup([[maybe_unused]] Runtime&) -> bool;

			[[nodiscard]] virtual auto on_post_startup([[maybe_unused]] Runtime&) -> bool;

			[[nodiscard]] virtual auto on_pre_tick([[maybe_unused]] Runtime&) -> bool;

			[[nodiscard]] virtual auto on_post_tick([[maybe_unused]] Runtime&) -> bool;

			[[nodiscard]] virtual auto on_pre_shutdown([[maybe_unused]] Runtime&) -> bool;

			[[nodiscard]] virtual auto on_post_shutdown([[maybe_unused]] Runtime&) -> bool;

		private:
			double pre_startup_time_ = 0.;
			double post_startup_time_ = 0.;
			double pre_shutdown_time_ = 0.;
			double post_shutdown_time_ = 0.;
		};
	} // namespace core // namespace core
} // namespace power_ronin // namespace power_ronin
