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
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../../include/dce/core/kernel.hpp"
#include "../../include/dce/env.hpp"
#include "../../include/dce/time_utils.hpp"

#include <chrono>

namespace dce::core {
	enum class KernelState : std::int_fast32_t {
		OFFLINE = 0
		, ONLINE = 1
		, RUNNING = -1
	};

	struct Kernel::Core final {
		KernelState kernel_state = KernelState::OFFLINE;
		std::vector<std::tuple<std::uint_fast16_t, std::unique_ptr<ISubsystem>>> subsystems = {};
		Runtime* runtime = nullptr;
	};

	Kernel::Kernel(const int _in_argc, const char* const * const _in_argv, const char* const * const _in_envp) : argc(_in_argc), argv(_in_argv), envp(_in_envp), core_(std::make_unique<Core>()) { }

	auto Kernel::create(const int _in_argc, const char* const* const _in_argv, const char* const* const _in_envp) -> std::unique_ptr<Kernel> {
		struct Factory final : Kernel {
			explicit Factory(const int _a, const char* const* const _b, const char* const* const _c) : Kernel(_a, _b, _c) { }
		};
		return std::make_unique<Factory>(_in_argc, _in_argv, _in_envp);
	}

	Kernel::~Kernel() = default;

	/* Startup runtime */
	auto Kernel::startup() const -> std::uint64_t {
		[[unlikely]] if (this->core_->kernel_state != KernelState::OFFLINE) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Invalid kernel state!");
		}
		std::filesystem::current_path("../../../");

		const auto tik = std::chrono::high_resolution_clock::now();

		/* Allocate state. */
		this->core_->runtime = new(std::nothrow) Runtime();
		[[unlikely]] if (!this->core_->runtime) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to allocate runtime!");
		}

		auto& proto = this->core_->runtime->protocol();

		/* Initialize core engine system. Print some basic info. */
		proto.critical("Initializing {} v.{}", ENGINE_NAME, ENGINE_VERSION);
		proto.info("System: {}", SYSTEM_NAME);
		proto.info("Using C++ 20! Compiler: {}", COMPILER_NAME);

		proto.separator();

		for (std::size_t i = 0; i < this->core_->subsystems.size(); ++i) {
			const auto& entry = this->core_->subsystems[i];
			const auto id = std::get<0>(entry);
			const auto& sys = std::get<1>(entry);
			const auto* const name = typeid(decltype(*sys)).name();
			const auto hash = typeid(decltype(*sys)).hash_code();

			proto.info("Found installed subsystem {} of {}:", i + 1, this->core_->subsystems.size());
			proto.info("\tID: {:#x}", id);
			proto.info("\tTypename: {}", name);
			proto.info("\tHash: {:#x}", hash);
			proto.info("\tName: {}", sys->name);
			proto.info("\tMask: {:#08b}", sys->subscribed_events);
		}

		/* Invoke "on_pre_startup()" on all subsystems, which have this event registered. */
		for (auto sys = this->core_->subsystems.begin(); sys != this->core_->subsystems.end(); std::advance(sys, 1)) {
			const auto& name = std::get<1>(*sys)->name;
			proto.critical(R"(Invoking kernel event "on_pre_startup" on subsystem interface "{}"...)", name);
			const auto tik2 = std::chrono::high_resolution_clock::now();
			[[unlikely]] if (std::get<1>(*sys)->subscribed_events & ServiceEvents::PRE_STARTUP && !std::get<1>(*sys)->
				on_pre_startup(*this->core_->runtime)) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Bad \"on_pre_startup\" call!");
			}
			const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			proto.info("OK! \"on_pre_startup\" invoked! {}s elapsed!", std::get<1>(*sys)->pre_startup_time_ = dur);
		}

		/* Startup state. */
		const auto state_clock = std::chrono::high_resolution_clock::now();
		proto.critical("Starting runtime...");
		this->core_->runtime->initialize();
		const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::high_resolution_clock::now() - state_clock).count()) / 1000000.0;
		proto.critical("State online! Required {}s!", dur);
		this->core_->kernel_state = KernelState::ONLINE;
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik).count();

		/* Invoke "on_post_startup()" on all subsystems, which have this event registered. */
		for (auto sys = this->core_->subsystems.rbegin(); sys != this->core_->subsystems.rend(); std::advance(sys, 1)) {
			const auto& name = std::get<1>(*sys)->name;
			proto.critical(R"(Invoking kernel event "on_post_startup" on subsystem interface "{}"...)", name);
			const auto tik2 = std::chrono::high_resolution_clock::now();
			[[unlikely]] if (std::get<1>(*sys)->subscribed_events & ServiceEvents::POST_STARTUP && !std::get<1>(*sys)->
				on_post_startup(*this->core_->runtime)) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Bad \"on_post_startup\" call!");
			}
			const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			proto.info("OK! \"on_post_startup\" invoked! {}s elapsed!", std::get<1>(*sys)->post_startup_time_ = dur);
		}

		proto.separator();
		proto.info("OK! System online! Boot took {}s!", static_cast<double>(duration) / 1000000.0);

		return duration;
	}

	/* Execute runtime */
	auto Kernel::execute() -> std::tuple<std::uint_fast32_t, std::uint8_t, std::uint64_t> {
		[[unlikely]] if (this->core_->kernel_state != KernelState::ONLINE || this->core_->runtime == nullptr) {
			return {0, 0, 0};
		}

		auto& proto = this->core_->runtime->protocol();
		proto.info("Entering runtime...");
		proto.separator();

		const auto tik = std::chrono::high_resolution_clock::now();
		std::uint_fast32_t cycles = 0;

		// Tick proc:
		auto tick = [&]() mutable -> bool {
			++cycles;

			/* Invoke "on_pre_tick()" on all subsystems, which have this event registered. */
			for (auto sys = this->core_->subsystems.begin(); sys != this->core_->subsystems.end(); std::advance(sys, 1)) {
				const auto tik2 = std::chrono::high_resolution_clock::now();
				[[unlikely]] if (std::get<1>(*sys)->subscribed_events & ServiceEvents::PRE_TICK && !std::get<1>(*sys)->on_pre_tick(*this->core_->runtime)) {
					return false;
				}
				const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
					std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
				std::get<1>(*sys)->pre_tick_time_ = dur;
			}

			/* Invoke "on_post_tick()" on all subsystems, which have this event registered. */
			for (auto sys = this->core_->subsystems.rbegin(); sys != this->core_->subsystems.rend(); std::advance(sys, 1)) {
				const auto tik2 = std::chrono::high_resolution_clock::now();
				[[unlikely]] if (std::get<1>(*sys)->subscribed_events & ServiceEvents::POST_TICK && !std::get<1>(*sys)->on_post_tick(*this->core_->runtime)) {
					return false;
				}
				const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
				std::get<1>(*sys)->post_tick_time_ = dur;
			}

			return true;
		};

		/* Enter game loop */
		[[likely]] while (tick());

		const auto tok = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tok - tik).count();
		proto.info("Terminated runtime! Cycles: {}", cycles);

		return {cycles, 0, duration};
	}

	/* Shutdown runtime */
	auto Kernel::shutdown() const -> std::uint64_t {
		[[unlikely]] if (this->core_->kernel_state != KernelState::ONLINE || this->core_->runtime == nullptr) {
			return 0;
		}

		const auto tik = std::chrono::high_resolution_clock::now();
		auto& proto = this->core_->runtime->protocol();

		/* Shutdown state. */
		proto.critical("Shutting down runtime...");
		this->core_->runtime->shutdown();

		/* Invoke "on_pre_shutdown()" on all subsystems, which have this event registered. */
		for (auto sys = this->core_->subsystems.begin(); sys != this->core_->subsystems.end(); ++sys) {
			const auto tik2 = std::chrono::high_resolution_clock::now();
			const auto& name = std::get<1>(*sys)->name;
			proto.critical(R"(Invoking kernel event "on_pre_shutdown" on subsystem interface "{}"...)", name);
			[[unlikely]] if (std::get<1>(*sys)->subscribed_events & ServiceEvents::PRE_SHUTDOWN && !std::get<1>(*sys)->on_pre_shutdown(*this->core_->runtime)) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Bad \"on_pre_shutdown\" call!");
			}
			const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			std::get<1>(*sys)->pre_shutdown_time_ = dur;
		}

		/* Invoke "on_post_shutdown()" on all subsystems, which have this event registered. */
		for (auto sys = this->core_->subsystems.rbegin(); sys != this->core_->subsystems.rend(); ++sys) {
			const auto tik2 = std::chrono::high_resolution_clock::now();
			const auto& name = std::get<1>(*sys)->name;
			proto.critical(R"(Invoking kernel event "on_post_shutdown" on subsystem interface "{}"...)", name);
			[[unlikely]] if (std::get<1>(*sys)->subscribed_events & ServiceEvents::POST_SHUTDOWN && !std::get<1>(*sys)->on_post_shutdown(*this->core_->runtime)) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Bad \"on_post_shutdown\" call!");
			}
			const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			std::get<1>(*sys)->post_shutdown_time_ = dur;
		}

		delete this->core_->runtime;
		this->core_->runtime = nullptr;

		this->core_->kernel_state = KernelState::OFFLINE;

		const auto tok = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tok - tik).count();

		return duration;
	}

	auto Kernel::installed_subsystems() const noexcept -> const std::vector<std::tuple<std::uint32_t, std::unique_ptr<ISubsystem>>
	>& {
		return this->core_->subsystems;
	}

	void Kernel::install_subsystem(std::unique_ptr<ISubsystem>&& _subsystem) const {
		/* Check if subsystem with id already exists: */
		for (const auto& sys : this->core_->subsystems) {
			if (std::get<1>(sys)->id == _subsystem->id) {
				return;
			}
		}

		this->core_->subsystems.emplace_back(std::make_tuple(_subsystem->id, std::move(_subsystem)));
	}

	auto Kernel::get_runtime() const noexcept -> Runtime* {
		return this->core_->runtime;
	}

	auto Kernel::uninstall_subsystem(const std::uint_fast16_t _id) const -> bool {
		/* Check if subsystem with id already exists: */
		for (std::size_t i = 0; i < this->core_->subsystems.size(); ++i) {
			/* If it exists, remove it */
			[[likely]] if (std::get<1>(this->core_->subsystems[i])->id == _id) {
				this->core_->subsystems.erase(this->core_->subsystems.begin() + i);
				return true;
			}
		}

		/* Not found */
		return false;
	}

	auto Kernel::lookup_subsystem(const std::uint_fast16_t _id) const -> bool {
		/* Check if subsystem with id already exists: */
		for (auto& service : this->core_->subsystems) {
			/* If it exists, remove it */
			if (std::get<1>(service)->id == _id) {
				return true;
			}
		}

		/* Not found */
		return false;
	}

	auto Kernel::install_subsystems(auto (*const _hook)(Kernel&) -> bool) -> std::size_t {
		[[likely]] if (_hook) {
			_hook(*this);
		}
		return this->core_->subsystems.size();
	}

	void Kernel::uninstall_all() const {
		this->core_->subsystems.clear();
	}
} // namespace dce::core // namespace dce::core
