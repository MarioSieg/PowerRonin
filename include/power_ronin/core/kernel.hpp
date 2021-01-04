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
#include <memory>
#include <tuple>
#include <vector>
#include <chrono>
#include <string_view>

#include "subsystem.hpp"
#include "../runtime.hpp"

namespace power_ronin
{
	class Runtime;

	namespace core
	{
		constexpr std::string_view ENGINE_NAME = "PowerRonin-Engine";
		constexpr float ENGINE_VERSION = 0.01f;

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
			[[nodiscard]] static auto create(const int _in_argc, const char** _in_argv, const char** _in_envp) -> std::unique_ptr<Kernel>;

			/// <summary>
			/// Argument count.
			/// </summary>
			const int argc;

			/// <summary>
			/// Argument vector.
			/// </summary>
			const char* const* const argv;

			/// <summary>
			/// Environment pointer.
			/// </summary>
			const char* const* const envp;

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
			[[nodiscard]] auto startup() const -> std::uint64_t;

			/// <summary>
			/// Enter simulation loop.
			/// </summary>
			auto execute() -> std::tuple<std::uint_fast32_t, std::uint8_t, std::uint64_t>;

			/// <summary>
			/// Shutdown engine.
			/// </summary>
			[[nodiscard]] auto shutdown() const -> std::uint64_t;

			/// <summary>
			/// Installs a new subsystem to the kernel and initializes all hooks
			/// </summary>
			/// <param name="_subsystem"></param>
			void install_subsystem(std::unique_ptr<ISubsystem>&& _subsystem) const;

			/// <summary>
			/// 
			/// </summary>
			/// <returns>Returns all installed subsystems.</returns>
			[[nodiscard]] auto installed_subsystems() const noexcept -> const std::vector<std::tuple<
				std::uint_fast16_t, std::unique_ptr<ISubsystem>>>&;

			/// <summary>
			/// 
			/// </summary>
			/// <returns>Returns the current runtime instance.</returns>
			[[nodiscard]] auto runtime() const noexcept -> Runtime*;

			/// <summary>
			/// Allocates and installs the subsystem T.
			/// </summary>
			/// <typeparam name="T"></typeparam>
			/// <typeparam name="...Q"></typeparam>
			/// <param name="_args"></param>
			/// <returns></returns>
			template <typename T, typename... Q> requires Subsystem<T>
			auto create_install_subsystem(Q&&..._args) -> Kernel&;

			/// <summary>
			/// Uninstalls a subsystem and removes all hooks
			/// </summary>
			/// <param name="_id"></param>
			/// <returns></returns>
			[[nodiscard]] auto uninstall_subsystem(std::uint_fast16_t _id) const -> bool;

			/// <summary>
			/// Returns true if the subsystem is installed, else false
			/// </summary>
			/// <param name="_id"></param>
			/// <returns></returns>
			[[nodiscard]] auto lookup_subsystem(std::uint_fast16_t _id) const -> bool;

			/// <summary>
			/// Install some subsystem via a hook.
			/// </summary>
			/// <param name="_hook"></param>
			/// <returns></returns>
			[[nodiscard]] auto install_subsystems(auto (*const _hook)(Kernel&) -> bool) -> std::size_t;


			/// <summary>
			/// Uninstalls all subsystems
			/// </summary>
			void uninstall_all() const;

		private:
			/// <summary>
			/// Create a new kernel instance.
			/// </summary>
			explicit Kernel(const int _in_argc, const char** _in_argv, const char** _in_envp);

			struct Core;
			const std::unique_ptr<Core> core_;
		};

		template <typename T, typename... Q> requires Subsystem<T> auto Kernel::create_install_subsystem(
			Q&&... _args) -> Kernel&
		{
			auto x = std::make_unique<T>(_args...);
			x->kernel_ = this;
			this->install_subsystem(std::move(x));
			return *this;
		}
	} // namespace core // namespace core
} // namespace power_ronin // namespace power_ronin
