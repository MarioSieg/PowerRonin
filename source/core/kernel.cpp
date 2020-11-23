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
#include "../../include/dce/utils.hpp"

#include <chrono>

namespace dce::core {
	enum class KernelState : std::uint8_t {
		OFFLINE
		, ONLINE
		, RUNNING
	};

	struct Kernel::Core final {
		KernelState kernel_state = KernelState::OFFLINE;
		std::vector<std::tuple<std::uint_fast16_t, std::unique_ptr<ISubsystem>>> subsystems = {};
		std::unique_ptr<State> state = nullptr;
	};

	Kernel::Kernel(const int _in_argc, const char* const * const _in_argv, const char* const * const _in_envp) : argc(_in_argc), argv(_in_argv), envp(_in_envp), core_(std::make_unique<Core>()) { }

	Kernel::~Kernel() = default;

	auto Kernel::create(const int _in_argc, const char* const* const _in_argv, const char* const* const _in_envp) -> std::unique_ptr<Kernel> {
		struct Factory final : Kernel {
			explicit Factory(const int a, const char* const* const b, const char* const* const c) : Kernel(a, b, c) { }
		};
		return std::make_unique<Factory>(_in_argc, _in_argv, _in_envp);
	}

	/* Startup runtime */
	auto Kernel::startup() const -> std::uint64_t {
		[[unlikely]] if (this->core_->kernel_state != KernelState::OFFLINE) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Invalid kernel state!");
		}
		std::filesystem::current_path("../../../");

		const auto tik = std::chrono::high_resolution_clock::now();

		/* Allocate state. */
		this->core_->state = std::make_unique<State>();

		auto& proto = this->core_->state->protocol();

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
		for (auto sys = this->core_->subsystems.begin(); sys != this->core_->subsystems.end(); ++sys) {
			const auto& name = std::get<1>(*sys)->name;
			proto.critical(R"(Invoking kernel event "on_pre_startup" on subsystem interface "{}"...)", name);
			const auto tik2 = std::chrono::high_resolution_clock::now();
			[[unlikely]] if (std::get<1>(*sys)->subscribed_events & ServiceEvents::PRE_STARTUP && !std::get<1>(*sys)->on_pre_startup(*this->core_->state)) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Bad \"on_pre_startup\" call!");
			}
			const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			proto.info("OK! \"on_pre_startup\" invoked! {}s elapsed!", std::get<1>(*sys)->pre_startup_time = dur);
		}

		/* Invoke "on_post_startup()" on all subsystems, which have this event registered. */
		for (auto sys = this->core_->subsystems.rbegin(); sys != this->core_->subsystems.rend(); ++sys) {
			const auto& name = std::get<1>(*sys)->name;
			proto.critical(R"(Invoking kernel event "on_post_startup" on subsystem interface "{}"...)", name);
			const auto tik2 = std::chrono::high_resolution_clock::now();
			[[unlikely]] if (std::get<1>(*sys)->subscribed_events & ServiceEvents::POST_STARTUP && !std::get<1>(*sys)->on_post_startup(*this->core_->state)) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Bad \"on_post_startup\" call!");
			}
			const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			proto.info("OK! \"on_post_startup\" invoked! {}s elapsed!", std::get<1>(*sys)->post_startup_time = dur);
		}

		/* Startup state. */
		const auto tik2 = std::chrono::high_resolution_clock::now();
		proto.critical("Starting state...");
		this->core_->state->start();
		const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;

		proto.critical("State online! Required {}s!", dur);
		this->core_->kernel_state = KernelState::ONLINE;
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik).count();

		proto.separator();

		proto.info("OK! System online! Boot took {}s!", static_cast<double>(duration) / 1000000.0);

		[[unlikely]] if (this->hook_startup != nullptr && !this->hook_startup()) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("\"hook_startup\" returned false!");
		}

		return duration;
	}

	/* Execute runtime */
	auto Kernel::execute() -> std::tuple<std::uint_fast32_t, std::uint8_t, std::uint64_t> {
		[[unlikely]] if (this->core_->kernel_state != KernelState::ONLINE || this->core_->state == nullptr) {
			return {0, 0, 0};
		}

		auto& proto = this->core_->state->protocol();
		proto.info("Entering runtime...");
		proto.separator();

		const auto tik = std::chrono::high_resolution_clock::now();
		std::uint_fast32_t cycles = 0;

		// Tick proc:
		auto tick = [&]() mutable -> bool {
			++cycles;

			/* Invoke "on_pre_tick()" on all subsystems, which have this event registered. */
			for (auto sys = this->core_->subsystems.begin(); sys != this->core_->subsystems.end(); ++sys) {
				const auto tik2 = std::chrono::high_resolution_clock::now();
				[[unlikely]] if (std::get<1>(*sys)->subscribed_events & ServiceEvents::PRE_TICK && !std::get<1>(*sys)->on_pre_tick(*this->core_->state)) {
					return false;
				}
				const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
				std::get<1>(*sys)->pre_tick_time = dur;
			}

			/* Invoke "on_post_tick()" on all subsystems, which have this event registered. */
			for (auto sys = this->core_->subsystems.rbegin(); sys != this->core_->subsystems.rend(); ++sys) {
				const auto tik2 = std::chrono::high_resolution_clock::now();
				[[unlikely]] if (std::get<1>(*sys)->subscribed_events & ServiceEvents::POST_TICK && !std::get<1>(*sys)->on_post_tick(*this->core_->state)) {
					return false;
				}
				const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
				std::get<1>(*sys)->post_tick_time = dur;
			}

			/* Update hook. */
			[[unlikely]] if (this->hook_tick != nullptr && !this->hook_tick(cycles)) {
				return false;
			}

			/* Update state. */
			this->core_->state->update();

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
		[[unlikely]] if (this->core_->kernel_state != KernelState::ONLINE || this->core_->state == nullptr) {
			return 0;
		}

		const auto tik = std::chrono::high_resolution_clock::now();
		auto& proto = this->core_->state->protocol();

		/* Shutdown state. */
		this->core_->state->end();

		/* Invoke "on_pre_shutdown()" on all subsystems, which have this event registered. */
		for (auto sys = this->core_->subsystems.begin(); sys != this->core_->subsystems.end(); ++sys) {
			const auto tik2 = std::chrono::high_resolution_clock::now();
			const auto& name = std::get<1>(*sys)->name;
			proto.critical(R"(Invoking kernel event "on_pre_shutdown" on subsystem interface "{}"...)", name);
			[[unlikely]] if (std::get<1>(*sys)->subscribed_events & ServiceEvents::PRE_SHUTDOWN && !std::get<1>(*sys)->on_pre_shutdown(*this->core_->state)) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Bad \"on_pre_shutdown\" call!");
			}
			const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			std::get<1>(*sys)->pre_shutdown_time = dur;
		}

		/* Invoke "on_post_shutdown()" on all subsystems, which have this event registered. */
		for (auto sys = this->core_->subsystems.rbegin(); sys != this->core_->subsystems.rend(); ++sys) {
			const auto tik2 = std::chrono::high_resolution_clock::now();
			const auto& name = std::get<1>(*sys)->name;
			proto.critical(R"(Invoking kernel event "on_post_shutdown" on subsystem interface "{}"...)", name);
			[[unlikely]] if (std::get<1>(*sys)->subscribed_events & ServiceEvents::POST_SHUTDOWN && !std::get<1>(*sys)->on_post_shutdown(*this->core_->state)) {
				throw MAKE_FATAL_ENGINE_EXCEPTION("Bad \"on_post_shutdown\" call!");
			}
			const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik2).count()) / 1000000.0;
			std::get<1>(*sys)->post_shutdown_time = dur;
		}

		this->core_->kernel_state = KernelState::OFFLINE;

		const auto tok = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tok - tik).count();

		[[unlikely]] if (this->hook_shutdown != nullptr && !this->hook_shutdown()) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("\"hook_shutdown\" returned false!");
		}
		return duration;
	}

	auto Kernel::installed_subsystems() const noexcept -> const std::vector<std::tuple<std::uint32_t, std::unique_ptr<ISubsystem>>>& {
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

	auto Kernel::get_state() noexcept -> std::unique_ptr<State>& {
		return this->core_->state;
	}

	auto Kernel::get_state() const noexcept -> const std::unique_ptr<State>& {
		return this->core_->state;
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

	auto Kernel::install_subsystems(auto (* const _hook)(Kernel&) -> bool) -> std::size_t {
		[[likely]] if (_hook) {
			_hook(*this);
		}
		return this->core_->subsystems.size();
	}

	void Kernel::uninstall_all() const {
		this->core_->subsystems.clear();
	}
} // namespace dce::core // namespace dce::core
