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

#include <string>
#include <unordered_map>

#include "proto.hpp"

namespace dce {
	class Runtime;

	enum class CommandExecutionResult: std::int8_t {
		OK = 0,
		COMMAND_DOES_NOT_EXIST = -1,
		ARGS_SEPARATOR_MISSING = -2,
		NO_ARGS_PROVIDED = -3,
		COMMAND_FUNCTOR_FAILED = -4,
	};

	/* Represents a command in the cmd. */
	struct Command final {
		std::string_view token = {};
		std::string_view help = {};
		auto (*functor)(Runtime&, std::string&&) -> bool = {};
		bool requires_root = false;
		bool requires_args = false;

		[[nodiscard]] auto operator()(Runtime& _rt, std::string&& _args) const -> bool;
	};

	inline auto Command::operator()(Runtime& _rt, std::string&& _args) const -> bool {
		return this->functor != nullptr ? this->functor(_rt, std::move(_args)) : false;
	}

	/* Contains all registered terminal commands. */
	class CmdDB final {
		friend class Runtime;
	public:
		static constexpr char ARGUMENT_SEPARATOR = '=';

		/* Analyze whole command string. */
		[[nodiscard]] auto analyze_and_call(Runtime& _rt, std::string&& _in) -> CommandExecutionResult;

		/* Calls the command. */
		[[nodiscard]] auto call(std::string_view _command, Runtime& _rt, std::string&& _args) -> bool;

		/* Pushes a new command. */
		[[nodiscard]] auto register_command(const Command& _command) -> bool;

		/* Returns a get_help string to the command. */
		[[nodiscard]] auto get_help(std::string_view _command) -> std::string_view;

		/* Returns true if the command is registered, else false. */
		[[nodiscard]] auto is_command_registered(std::string_view _command) const -> bool;

		[[nodiscard]] auto get_registry_map() & noexcept -> std::unordered_map<std::string_view, Command>&;

		[[nodiscard]] auto get_registry_map() const & noexcept -> const std::unordered_map<std::string_view, Command>&;

		[[nodiscard]] auto get_registry_map() && noexcept -> std::unordered_map<std::string_view, Command>&&;

		[[nodiscard]] auto get_history() const & noexcept -> const std::vector<std::string>&;

		[[nodiscard]] auto get_history() && noexcept -> std::vector<std::string>&&;

		void clear_history();

	private:
		void install_common_commands();
		std::unordered_map<std::string_view, Command> commands_ = {};
		std::vector<std::string> history_ = {};
	};
} // namespace dce // namespace dce
