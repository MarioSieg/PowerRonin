// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: cmddb.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include <string>
#include <unordered_map>

#include "proto.hpp"

namespace dce {
	class State;

	enum class CommandExecutionResult: std::int8_t {
		OK = 0
		, COMMAND_DOES_NOT_EXIST = -1
		, ARGS_SEPARATOR_MISSING = -2
		, NO_ARGS_PROVIDED = -3
		, COMMAND_FUNCTOR_FAILED = -4
		,
	};

	/* Represents a command in the cmd. */
	struct Command final {
		std::string_view token = {};
		std::string_view help = {};
		auto (*functor)(State &, std::string &&) -> bool = {};
		bool requires_root = false;
		bool requires_args = false;

		[[nodiscard]] auto operator()(State &_state, std::string &&_args) const -> bool;
	};

	inline auto Command::operator()(State &_state, std::string &&_args) const -> bool {
		return this->functor != nullptr ? this->functor(_state, std::move(_args)) : false;
	}

	/* Contains all registered terminal commands. */
	class CmdDB final {
		friend class State;
	public:
		static constexpr char ARGUMENT_SEPARATOR = '=';

		/* Analyze whole command string. */
		[[nodiscard]] auto analyze_and_call(State &_state, std::string &&_in) -> CommandExecutionResult;

		/* Calls the command. */
		[[nodiscard]] auto call(std::string_view _command, State &_state, std::string &&_args) -> bool;

		/* Pushes a new command. */
		[[nodiscard]] auto register_command(const Command &_command) -> bool;

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
