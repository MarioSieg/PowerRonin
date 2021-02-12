#pragma once

#include <cstdint>
#include <memory>
#include <tuple>
#include <vector>
#include <chrono>

#include "Subsystem.hpp"
#include "../Runtime.hpp"

namespace PowerRonin
{
	class Runtime;

	namespace Core
	{
		constexpr std::string_view EngineName = "PowerRonin-Engine";
		constexpr float EngineVersion = .01F;

		class Kernel;
		class ISubsystem;

		template <typename... T>
		concept Subsystem = std::is_base_of<ISubsystem, T...>::value;

		/// <summary>
		/// Represents an engine kernel, containing all subsystems.
		/// </summary>
		class Kernel
		{
		public:
			[[nodiscard]] static auto Create(const int inArgc, const char** inArgv, const char** inEnvp) -> std::unique_ptr<Kernel>;

			/// <summary>
			/// Argument count.
			/// </summary>
			const int ArgCount;

			/// <summary>
			/// Argument vector.
			/// </summary>
			const char* const* const ArgVector;

			/// <summary>
			/// Environment pointer.
			/// </summary>
			const char* const* const EnvPtr;

			/// <summary>
			/// Delete copy and move constructor and assignment operators.
			/// </summary>
			Kernel(const Kernel&) = delete;

			/// <summary>
			/// Delete copy and move constructor and assignment operators.
			/// </summary>
			Kernel(Kernel&&) = delete;

			/// <summary>
			/// Delete copy and move constructor and assignment operators.
			/// </summary>
			auto operator=(const Kernel&) -> Kernel& = delete;

			/// <summary>
			/// Delete copy and move constructor and assignment operators.
			/// </summary>
			/// <returns></returns>
			auto operator=(Kernel&&) -> Kernel& = delete;

			/// <summary>
			/// Dctor.
			/// </summary>
			~Kernel();

			/// <summary>
			/// Startup engine.
			/// </summary>
			[[nodiscard]] auto Startup() const -> std::uint64_t;

			/// <summary>
			/// Enter simulation loop.
			/// </summary>
			auto Execute() -> std::tuple<std::uint_fast32_t, std::uint8_t, std::uint64_t>;

			/// <summary>
			/// Shutdown engine.
			/// </summary>
			[[nodiscard]] auto Shutdown() const -> std::uint64_t;

			/// <summary>
			/// Installs a new subsystem to the kernel and initializes all hooks
			/// </summary>
			/// <param name="subSystem"></param>
			void InstallSubsystem(std::unique_ptr<ISubsystem>&& subSystem) const;

			/// <summary>
			/// 
			/// </summary>
			/// <returns>Returns all installed subsystems.</returns>
			[[nodiscard]] auto InstalledSubsystems() const noexcept
			-> const std::vector<std::tuple<std::uint_fast16_t, std::unique_ptr<ISubsystem>>>&;

			/// <summary>
			/// 
			/// </summary>
			/// <returns>Returns the current runtime instance.</returns>
			[[nodiscard]] auto Runtime() const noexcept -> class Runtime&;

			/// <summary>
			/// Allocates and installs the subsystem T.
			/// </summary>
			/// <typeparam name="T"></typeparam>
			/// <typeparam name="...Q"></typeparam>
			/// <param name="args"></param>
			/// <returns></returns>
			template <typename T, typename... Q> requires Subsystem<T>
			auto CreateInstallSubsystem(Q&&... args) -> Kernel&;

			/// <summary>
			/// Uninstalls a subsystem and removes all hooks
			/// </summary>
			/// <param name="id"></param>
			/// <returns></returns>
			[[nodiscard]] auto UninstallSubsystem(std::uint_fast16_t id) const -> bool;

			/// <summary>
			/// Returns true if the subsystem is installed, else false
			/// </summary>
			/// <param name="id"></param>
			/// <returns></returns>
			[[nodiscard]] auto LookupSubsystem(std::uint_fast16_t id) const -> bool;

			/// <summary>
			/// Install some subsystem via a hook.
			/// </summary>
			/// <param name="installerHook"></param>
			/// <returns></returns>
			auto InstallSubsystems(const std::function<void(Kernel&)>& installerHook) -> std::size_t;


			/// <summary>
			/// Uninstalls all subsystems
			/// </summary>
			void UninstallAll() const;

		private:
			/// <summary>
			/// Create a new kernel instance.
			/// </summary>
			explicit Kernel(const int argc, const char** const argv, const char** const envp);

			struct Core;
			const std::unique_ptr<Core> systemHandle;
		};

		template <typename T, typename... Q> requires Subsystem<T>
		auto Kernel::CreateInstallSubsystem(Q&&... args) -> Kernel&
		{
			auto x = std::make_unique<T>(args...);
			this->InstallSubsystem(std::move(x));
			return *this;
		}
	} // namespace Core // namespace Core
} // namespace PowerRonin // namespace PowerRonin
