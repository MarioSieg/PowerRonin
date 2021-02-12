#pragma once

#include <cstdint>
#include <limits>
#include <string_view>

namespace PowerRonin
{
	class Runtime;

	namespace Core
	{
		// Bitmask to subscribe to subsystem events
		struct ServiceEvents
		{
			enum Enum : std::uint8_t
			{
				None = 0,
				PreStartup = 1 << 0,
				PostStartup = 1 << 1,
				PreTick = 1 << 2,
				PostTick = 1 << 3,
				PreShutdown = 1 << 4,
				PostShutdown = 1 << 5,
				All = 0xFF
			};
		};

		/* Represents an engine subsystem (base interface) */
		class ISubsystem
		{
			friend class Kernel;

		protected:
			ISubsystem(const std::string_view name, const std::underlying_type<ServiceEvents::Enum>::type subscribedEvents) noexcept;

		public:
			/* Name of the subsystem */
			const std::string_view Name;

			/* Subscribed event for this subsystem */
			const std::underlying_type<ServiceEvents::Enum>::type SubscribedEvents;

			/* 16-bit short UUID for this subsystem */
			const std::uint_fast16_t UniqueID;

			ISubsystem(const ISubsystem&) = delete;
			ISubsystem(ISubsystem&&) = delete;
			auto operator=(const ISubsystem&) -> ISubsystem& = delete;
			auto operator=(ISubsystem&&) -> ISubsystem& = delete;

			/* Virtual destructor */
			virtual ~ISubsystem() = default;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto PreStartupTime() const noexcept -> double;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto PostStartupTime() const noexcept -> double;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto PreShutdownTime() const noexcept -> double;

			/* Returns the kernel event time in ms. */
			[[nodiscard]] auto PostShutdownTime() const noexcept -> double;

		protected:
			virtual void OnPreStartup([[maybe_unused]] Runtime&);

			virtual void OnPostStartup([[maybe_unused]] Runtime&);

			virtual void OnPreTick([[maybe_unused]] Runtime&);

			virtual void OnPostTick([[maybe_unused]] Runtime&);

			virtual void OnPreShutdown([[maybe_unused]] Runtime&);

			virtual void OnPostShutdown([[maybe_unused]] Runtime&);

		private:
			double preStartupTime = 0.;
			double postStartupTime = 0.;
			double preShutdownTime = 0.;
			double postShutdownTime = 0.;
		};
	} // namespace Core // namespace Core
} // namespace PowerRonin // namespace PowerRonin
