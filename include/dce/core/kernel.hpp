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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

#include "subsystem.hpp"
#include "../../../include/dce/runtime.hpp"
#include <cstdint>
#include <memory>
#include <tuple>
#include <vector>

namespace dce {
	class Runtime;

	namespace core {
		constexpr std::string_view ENGINE_NAME = "Dreamcast-Engine";
		constexpr float ENGINE_VERSION = 0.01f;

		class Kernel;
		class ISubsystem;

		template <typename... T> concept Subsystem = std::is_base_of<ISubsystem, T...>::value;

		/* Represents an engine kernel, containing all subsystems  */
		class Kernel {
		public:
			[[nodiscard]] static auto create(const int _in_argc
			                                 , const char* const* const _in_argv
			                                 , const char* const* const _in_envp) -> std::unique_ptr<Kernel>;

			/* Argument count */
			const int argc;

			/* Argument vector */
			const char* const* const argv;

			/* Environment vector pointer */
			const char* const* const envp;

			/* Callback hooks */
			auto (*hook_startup)() -> bool = nullptr;
			auto (*hook_tick)(std::uint_fast32_t _cycle) -> bool = nullptr;
			auto (*hook_shutdown)() -> bool = nullptr;

			/* Delete copy and move constructor and assignment operators */
			Kernel(const Kernel&) = delete;
			Kernel(Kernel&&) = delete;
			auto operator=(const Kernel&) -> Kernel& = delete;
			auto operator=(Kernel&&) -> Kernel& = delete;

			/* Destructor */
			~Kernel();

			/* Startup runtime */
			auto startup() const -> std::uint64_t;

			/* Execute runtime */
			auto execute() -> std::tuple<std::uint_fast32_t, std::uint8_t, std::uint64_t>;

			/* Shutdown runtime */
			auto shutdown() const -> std::uint64_t;

			/* Installs a new subsystem to the kernel and initializes all hooks */
			void install_subsystem(std::unique_ptr<ISubsystem>&& _subsystem) const;

			/* Returns installed subsystems */
			[[nodiscard]] auto installed_subsystems() const noexcept -> const std::vector<std::tuple<
				std::uint_fast16_t, std::unique_ptr<ISubsystem>>>&;

			/* Returns the current simulation state. */
			[[nodiscard]] auto get_runtime() const noexcept -> Runtime*;

			/* Allocates and installs the subsystem T. */
			template <typename T, typename... Q> requires Subsystem<T> auto create_install_subsystem(Q&&... /*args*/) -> Kernel&;

			/* Uninstalls a subsystem and removes all hooks */
			[[nodiscard]] auto uninstall_subsystem(std::uint_fast16_t _id) const -> bool;

			/* Returns true if the subsystem is installed, else false */
			[[nodiscard]] auto lookup_subsystem(std::uint_fast16_t _id) const -> bool;

			/* Install some subsystem via a hook. */
			auto install_subsystems(auto (* _hook)(Kernel&) -> bool) -> std::size_t;

			/* Uninstalls all subsystems */
			void uninstall_all() const;

		private:
			/* Create a new kernel instance */
			explicit Kernel(int _in_argc, const char* const* _in_argv, const char* const* _in_envp);

			/* Core pimpl (pointer to implementation) */
			struct Core;
			const std::unique_ptr<Core> core_;
		};

		template <typename T, typename... Q> requires Subsystem<T> auto Kernel::create_install_subsystem(Q&&... _args) -> Kernel& {
			this->install_subsystem(std::move(std::make_unique<T>(_args...)));
			return *this;
		}
	} // namespace core // namespace core
} // namespace dce // namespace dce
