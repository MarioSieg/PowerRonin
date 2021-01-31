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

#include "../../include/power_ronin/core/kernel.hpp"
#include "../../include/power_ronin/env.hpp"
#include "core.hpp"

namespace PowerRonin::Core
{
	Kernel::Kernel(const int argc, const char** argv, const char** envp) : ArgCount(argc), ArgVector(argv), EnvPtr(envp), systemHandle(std::make_unique<Core>()) { }

	auto Kernel::Create(const int inArgc, const char** inArgv, const char** inEnvp) -> std::unique_ptr<Kernel>
	{
		struct Factory final : Kernel
		{
			Factory(const int inArgc, const char** inArgv, const char** inEnvp) : Kernel(inArgc, inArgv, inEnvp) {}
		};
		return std::make_unique<Factory>(inArgc, inArgv, inEnvp);
	}

	static void PrintSubsystemInfo(AsyncProtocol& proto, const std::vector<std::tuple<std::uint_fast16_t, std::unique_ptr<ISubsystem>>>& systems);

	Kernel::~Kernel() = default;

	/* Startup runtime */
	auto Kernel::Startup() const -> std::uint64_t
	{
		if (this->systemHandle->KernelState != KernelState::Offline) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Invalid kernel state!");
		}

		std::filesystem::current_path("../../../");

		const auto tik = std::chrono::high_resolution_clock::now();

		/* Allocate state. */
		this->systemHandle->Runtime = std::make_unique<class Runtime>();
		if (!this->systemHandle->Runtime) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to allocate runtime!");
		}

		auto& proto = this->systemHandle->Runtime->Protocol();

		/* Initialize Core engine system. Print some basic info. */
		proto.Critical("Initializing {} v.{}", EngineName, EngineVersion);
		proto.Info("System: {}", SystemName);
		proto.Info("Using C++ 20! Compiler: {}", CompilerName);

		proto.Separator();

		this->systemHandle->PrintSubsystemInfo();
		this->systemHandle->DispatchPreStartup();

		/* Startup state. */
		const auto stateClock = std::chrono::high_resolution_clock::now();
		proto.Critical("Starting runtime...");
		this->systemHandle->Runtime->Initialize();
		const auto dur = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - stateClock).count()) / 1000000.0;
		proto.Critical("State online! Required {}s!", dur);
		this->systemHandle->KernelState = KernelState::Online;

		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tik).count();

		this->systemHandle->DispatchPostStartup();
		
		proto.Separator();
		proto.Info("OK! System online! Boot took {}s!", static_cast<double>(duration) / 1000000.0);

		return duration;
	}

	/* Execute runtime */
	auto Kernel::Execute() -> std::tuple<std::uint_fast32_t, std::uint8_t, std::uint64_t>
	{
		if (this->systemHandle->KernelState != KernelState::Online || this->systemHandle->Runtime == nullptr) [[unlikely]]
		{
			return {0, 0, 0};
		}

		auto& proto = this->systemHandle->Runtime->Protocol();
		proto.Info("Entering runtime...");
		proto.Separator();

		const auto tik = std::chrono::high_resolution_clock::now();
		std::uint_fast32_t cycles = 0;

		// Tick proc:
		auto tick = [&]() mutable -> bool
		{
			++cycles;
			this->systemHandle->DispatchPreTick();
			this->systemHandle->DispatchPostTick();
			return true;
		};

		/* Enter runtime loop */
		while (tick()) [[likely]];

		const auto tok = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tok - tik).count();
		proto.Info("Terminated runtime! Cycles: {}", cycles);

		return {cycles, 0, duration};
	}

	/* Shutdown runtime */
	auto Kernel::Shutdown() const -> std::uint64_t
	{
		if (this->systemHandle->KernelState != KernelState::Online || this->systemHandle->Runtime == nullptr) [[unlikely]]
		{
			return 0;
		}

		const auto tik = std::chrono::high_resolution_clock::now();
		auto& proto = this->systemHandle->Runtime->Protocol();

		/* Shutdown state. */
		proto.Critical("Shutting down runtime...");
		this->systemHandle->Runtime->Shutdown();

		this->systemHandle->DispatchPreShutdown();
		this->systemHandle->DispatchPostShutdown();

		this->systemHandle->Runtime.reset();
		this->systemHandle->KernelState = KernelState::Offline;

		const auto tok = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tok - tik).count();

		return duration;
	}

	auto Kernel::InstalledSubsystems() const noexcept -> const std::vector<std::tuple<::uint32_t, std::unique_ptr<ISubsystem>>>&
	{
		return this->systemHandle->Subsystems;
	}

	void Kernel::InstallSubsystem(std::unique_ptr<ISubsystem>&& subSystem) const
	{
		/* Check if subsystem with id already exists: */
		for (const auto& sys : this->systemHandle->Subsystems)
		{
			if (std::get<1>(sys)->UniqueID == subSystem->UniqueID) [[unlikely]]
			{
				return;
			}
		}

		this->systemHandle->Subsystems.emplace_back(std::make_tuple(subSystem->UniqueID, std::move(subSystem)));
	}

	auto Kernel::Runtime() const noexcept -> class Runtime&
	{
		return *this->systemHandle->Runtime;
	}

	auto Kernel::UninstallSubsystem(const std::uint_fast16_t id) const -> bool
	{
		for (std::size_t i = 0; i < this->systemHandle->Subsystems.size(); ++i)
		{
			if (std::get<1>(this->systemHandle->Subsystems[i])->UniqueID == id) [[unlikely]]
			{
				this->systemHandle->Subsystems.erase(this->systemHandle->Subsystems.begin() + i);
				return true;
			}
		}

		/* Not found */
		return false;
	}

	auto Kernel::LookupSubsystem(const std::uint_fast16_t id) const -> bool
	{
		for (auto& service : this->systemHandle->Subsystems)
		{
			if (std::get<1>(service)->UniqueID == id) [[likely]]
			{
				return true;
			}
		}

		/* Not found */
		return false;
	}

	auto Kernel::InstallSubsystems(const std::function<void(Kernel&)>& installerHook) -> std::size_t
	{
		installerHook(*this);
		return this->systemHandle->Subsystems.size();
	}

	void Kernel::UninstallAll() const
	{
		this->systemHandle->Subsystems.clear();
	}
} // namespace PowerRonin::Core // namespace PowerRonin::Core
