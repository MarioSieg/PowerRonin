// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: kernel.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "../../include/dce/core/kernel.hpp"
#include "../../include/dce/env.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace dce::core {
	enum class KernelState : std::uint8_t {
		Offline
		, Online
		, Running
		,
	};

	struct Kernel::Core final {
		KernelState kernel_state = KernelState::Offline;
		std::vector<std::tuple<std::uint_fast16_t, std::unique_ptr<ISubsystem>>> services = {};
		std::unique_ptr<State> state = nullptr;
	};

	Kernel::Kernel(const int in_argc, const char *const *const in_argv, const char *const *const in_envp) : argc(in_argc),
		argv(in_argv), envp(in_envp), core(std::make_unique<Core>()) { }

	Kernel::~Kernel() = default;

	auto Kernel::create(const int in_argc, const char *const*const in_argv
	                    , const char *const*const in_envp) -> std::unique_ptr<Kernel> {
		struct Factory final : Kernel {
			explicit Factory(const int a, const char *const*const b, const char *const*const c) : Kernel(a, b, c) { }
		};
		return std::make_unique<Factory>(in_argc, in_argv, in_envp);
	}

	/* Startup runtime */
	auto Kernel::startup() const -> std::tuple<bool, std::uint64_t> {
		[[unlikely]] if (this->core->kernel_state != KernelState::Offline) {
			return {false, 0};
		}

		const auto tik = std::chrono::high_resolution_clock::now();

		/* Allocate state. */
		this->core->state = std::make_unique<State>();

		auto &proto = this->core->state->protocol();

		/* Initialize core engine system. Print some basic info. */
		proto.critical("Initializing {} v.{}", ENGINE_NAME, ENGINE_VERSION);
		proto.info("System: {}", SYSTEM_NAME);
		proto.info("Using C++ 20! Compiler: {}", COMPILER_NAME);

		proto.separator();

		for (std::size_t i = 0; i < this->core->services.size(); ++i) {
			const auto &entry = this->core->services[i];
			const auto id = std::get<0>(entry);
			const auto &sys = std::get<1>(entry);
			const auto *const name = typeid(decltype(*sys)).name();
			const auto hash = typeid(decltype(*sys)).hash_code();

			proto.info("Found installed subsystem {} of {}:", i + 1, this->core->services.size());
			proto.info("\tID: {:#x}", id);
			proto.info("\tTypename: {}", name);
			proto.info("\tHash: {:#x}", hash);
			proto.info("\tName: {}", sys->name);
			proto.info("\tMask: {:#08b}", sys->subscribed_events);
		}
		/* Invoke "on_pre_startup()" on all subsystems, which have this event registered. */
		for (auto sys = this->core->services.begin(); sys != this->core->services.end(); ++sys) {
			const auto &name = std::get<1>(*sys)->name;
			proto.critical(R"(Invoking kernel event "on_pre_startup" on subsystem interface "{}"...)", name);
			const auto tik2 = std::chrono::high_resolution_clock::now();
			[[unlikely]] if ((std::get<1>(*sys)->subscribed_events & ServiceEvents::PRE_STARTUP) != 0 && !std::get<1>(*sys)->
				on_pre_startup(*this->core->state)) {
				proto.error(R"(Event "on_pre_startup" on subsystem "{}" returned "false"!)", name);
				return {false, 0};
			}
			const double dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
				std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			proto.info("OK! \"on_pre_startup\" invoked! {}s elapsed!", std::get<1>(*sys)->pre_startup_time = dur);
		}

		/* Invoke "on_post_startup()" on all subsystems, which have this event registered. */
		for (auto sys = this->core->services.rbegin(); sys != this->core->services.rend(); ++sys) {
			const auto &name = std::get<1>(*sys)->name;
			proto.critical(R"(Invoking kernel event "on_post_startup" on subsystem interface "{}"...)", name);
			const auto tik2 = std::chrono::high_resolution_clock::now();
			[[unlikely]] if ((std::get<1>(*sys)->subscribed_events & ServiceEvents::POST_STARTUP) != 0 && !std::get<1>(*sys)->
				on_post_startup(*this->core->state)) {
				proto.error(R"(Event "on_post_startup" on subsystem "{}" returned "false"!)", name);
				return {false, 0};
			}
			const double dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
				std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			proto.info("OK! \"on_post_startup\" invoked! {}s elapsed!", std::get<1>(*sys)->post_startup_time = dur);
		}

		/* Startup state. */
		const auto tik2 = std::chrono::high_resolution_clock::now();
		proto.critical("Starting state...");
		this->core->state->start();
		const double dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;

		proto.critical("State online! Required {}s!", dur);
		this->core->kernel_state = KernelState::Online;
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::high_resolution_clock::now() - tik).count();

		proto.separator();

		proto.info("OK! System online! Boot took {}s!", static_cast<double>(duration) / 1000000.0);

		[[unlikely]] if (this->hook_startup != nullptr) {
			return {this->hook_startup(), duration};
		}

		return {true, duration};
	}

	/* Execute runtime */
	auto Kernel::execute() -> std::tuple<bool, std::uint_fast32_t, std::uint8_t, std::uint64_t> {
		[[unlikely]] if (this->core->kernel_state != KernelState::Online || this->core->state == nullptr) {
			return {false, 0, 0, 0};
		}

		auto &proto = this->core->state->protocol();
		proto.info("Entering runtime...");
		proto.separator();

		const auto tik = std::chrono::high_resolution_clock::now();
		std::uint_fast32_t cycles = 0;

		// Tick proc:
		auto tick = [&]() mutable -> bool {
			++cycles;

			/* Invoke "on_pre_tick()" on all subsystems, which have this event registered. */
			for (auto sys = this->core->services.begin(); sys != this->core->services.end(); ++sys) {
				const auto tik2 = std::chrono::high_resolution_clock::now();
				[[unlikely]] if ((std::get<1>(*sys)->subscribed_events & ServiceEvents::PRE_TICK) != 0 && !std::get<1>(*sys)->
					on_pre_tick(*this->core->state)) {
					return false;
				}
				const double dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
					std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
				std::get<1>(*sys)->pre_tick_time = dur;
			}

			/* Invoke "on_post_tick()" on all subsystems, which have this event registered. */
			for (auto sys = this->core->services.rbegin(); sys != this->core->services.rend(); ++sys) {
				const auto tik2 = std::chrono::high_resolution_clock::now();
				[[unlikely]] if ((std::get<1>(*sys)->subscribed_events & ServiceEvents::POST_TICK) != 0 && !std::get<1>(*sys)->
					on_post_tick(*this->core->state)) {
					return false;
				}
				const double dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
					std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
				std::get<1>(*sys)->post_tick_time = dur;
			}

			/* Update hook. */
			[[unlikely]] if (this->hook_tick != nullptr && !this->hook_tick(cycles)) {
				return false;
			}

			/* Update state. */
			this->core->state->update();

			return true;
		};

		/* Enter game loop */
		[[likely]] while (tick());

		const auto tok = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tok - tik).count();
		proto.info("Terminated runtime! Cycles: {}", cycles);

		return {true, cycles, 0, duration};
	}

	/* Shutdown runtime */
	auto Kernel::shutdown() const -> std::tuple<bool, std::uint64_t> {
		[[unlikely]] if (this->core->kernel_state != KernelState::Online || this->core->state == nullptr) {
			return {false, 0};
		}

		const auto tik = std::chrono::high_resolution_clock::now();
		auto &proto = this->core->state->protocol();

		/* Shutdown state. */
		this->core->state->end();

		/* Invoke "on_pre_shutdown()" on all subsystems, which have this event registered. */
		for (auto sys = this->core->services.begin(); sys != this->core->services.end(); ++sys) {
			const auto tik2 = std::chrono::high_resolution_clock::now();
			const auto &name = std::get<1>(*sys)->name;
			proto.critical(R"(Invoking kernel event "on_pre_shutdown" on subsystem interface "{}"...)", name);
			[[unlikely]] if ((std::get<1>(*sys)->subscribed_events & ServiceEvents::PRE_SHUTDOWN) != 0 && !std::get<1>(*sys)->
				on_pre_shutdown(*this->core->state)) {
				proto.error(R"(Event "on_pre_shutdown" on subsystem "{}" returned "false"!)", name);
				return {false, 0};
			}
			const double dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
				std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			std::get<1>(*sys)->pre_shutdown_time = dur;
		}

		/* Invoke "on_post_shutdown()" on all subsystems, which have this event registered. */
		for (auto sys = this->core->services.rbegin(); sys != this->core->services.rend(); ++sys) {
			const auto tik2 = std::chrono::high_resolution_clock::now();
			const auto &name = std::get<1>(*sys)->name;
			proto.critical(R"(Invoking kernel event "on_post_shutdown" on subsystem interface "{}"...)", name);
			[[unlikely]] if ((std::get<1>(*sys)->subscribed_events & ServiceEvents::POST_SHUTDOWN) != 0 && !std::get<1>(*sys)->
				on_post_shutdown(*this->core->state)) {
				proto.error(R"(Event "on_post_shutdown" on subsystem "{}" returned "false"!)", name);
				return {false, 0};
			}
			const double dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
				std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			std::get<1>(*sys)->post_shutdown_time = dur;
		}

		this->core->kernel_state = KernelState::Offline;

		const auto tok = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tok - tik).count();

		[[unlikely]] if (this->hook_shutdown != nullptr) {
			return {this->hook_shutdown(), duration};
		}
		return {true, duration};
	}

	auto Kernel::installed_subsystems() const noexcept -> const std::vector<std::tuple<
		std::uint32_t, std::unique_ptr<ISubsystem>>>& {
		return this->core->services;
	}

	auto Kernel::install_subsystem(std::unique_ptr<ISubsystem> &&subsystem) const -> bool {
		/* Check if subsystem with id already exists: */
		for (const auto &sys : this->core->services) {
			if (std::get<1>(sys)->id == subsystem->id) {
				return false;
			}
		}

		this->core->services.emplace_back(std::make_tuple(subsystem->id, std::move(subsystem)));

		return true;
	}

	auto Kernel::get_state() noexcept -> std::unique_ptr<State>& {
		return this->core->state;
	}

	auto Kernel::get_state() const noexcept -> const std::unique_ptr<State>& {
		return this->core->state;
	}

	auto Kernel::uninstall_subsystem(const std::uint_fast16_t id) const -> bool {
		/* Check if subsystem with id already exists: */
		for (std::size_t i = 0; i < this->core->services.size(); ++i) {
			/* If it exists, remove it */
			[[likely]] if (std::get<1>(this->core->services[i])->id == id) {
				this->core->services.erase(this->core->services.begin() + i);
				return true;
			}
		}

		/* Not found */
		return false;
	}

	auto Kernel::lookup_subsystem(const std::uint_fast16_t id) const -> bool {
		/* Check if subsystem with id already exists: */
		for (auto &service : this->core->services) {
			/* If it exists, remove it */
			if (std::get<1>(service)->id == id) {
				return true;
			}
		}

		/* Not found */
		return false;
	}

	auto Kernel::install_subsystems(auto (* const hook)(Kernel &) -> bool) -> std::tuple<bool, std::size_t> {
		const auto size = this->core->services.size();
		return {hook(*this) && this->core->services.size() > size, this->core->services.size()};
	}

	void Kernel::uninstall_all() const {
		this->core->services.clear();
	}
} // namespace dce::core // namespace dce::core
