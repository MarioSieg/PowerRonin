// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: cmddb.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "../include/dce/cmddb.hpp"
#include "../include/dce/json_impl.hpp"
#include "../include/dce/state.hpp"
#include "gui/theme.hpp"
#include <string>

namespace dce {

	extern void register_common_commands(CmdDB &);

	auto CmdDB::analyze_and_call(State &_state, std::string &&_in) -> CommandExecutionResult {
		/* Add to history: */
		this->history_.push_back(_in);

		/* Search for existing command! */
		std::string_view command = "";
		for (const auto &[first, _] : this->commands_) {
			if (_in.starts_with(first)) {
				command = first;
				break;
			}
		}

		/* Command not found. */
		if (command == "") {
			return CommandExecutionResult::COMMAND_DOES_NOT_EXIST;
		}

		const auto &cmd = commands_[command];

		/* Remove command. */
		_in.erase(0, command.size());

		/* Check if command had any arguments (=) sign. */
		if (cmd.requires_args) {
			if (_in[0] == ARGUMENT_SEPARATOR) {
				/* Remove  */
				_in.erase(_in.begin());

				if (_in.empty()) {
					return CommandExecutionResult::NO_ARGS_PROVIDED;
				}
			}
			else {
				return CommandExecutionResult::ARGS_SEPARATOR_MISSING;
			}
		}

		/* Call functor. */
		return cmd(_state, std::move(_in)) ? CommandExecutionResult::OK : CommandExecutionResult::COMMAND_FUNCTOR_FAILED;
	}

	auto CmdDB::call(const std::string_view _command, State &_state, std::string &&_args) -> bool {
		if (!commands_.contains(_command)) {
			return false;
		}
		return commands_[_command](_state, std::move(_args));
	}

	auto CmdDB::register_command(const Command &_command) -> bool {
		if (commands_.contains(_command.token)) {
			return false;
		}
		commands_.insert({_command.token, _command});
		return true;
	}

	auto CmdDB::get_help(const std::string_view _command) -> std::string_view {
		if (commands_.contains(_command)) {
			return commands_[_command].help;
		}
		return "";
	}

	auto CmdDB::is_command_registered(const std::string_view _command) const -> bool {
		return commands_.contains(_command);
	}

	auto CmdDB::get_registry_map() & noexcept -> std::unordered_map<std::string_view, Command>& {
		return this->commands_;
	}

	auto CmdDB::get_registry_map() const & noexcept -> const std::unordered_map<std::string_view, Command>& {
		return this->commands_;
	}

	auto CmdDB::get_registry_map() && noexcept -> std::unordered_map<std::string_view, Command>&& {
		return std::move(this->commands_);
	}

	auto CmdDB::get_history() const & noexcept -> const std::vector<std::string>& {
		return this->history_;
	}

	auto CmdDB::get_history() && noexcept -> std::vector<std::string>&& {
		return std::move(this->history_);
	}

	void CmdDB::clear_history() {
		this->commands_.clear();
	}

	void CmdDB::install_common_commands() {
		register_common_commands(*this);
	}

	void register_common_commands(CmdDB &_cdb) {
		auto reg = [&](Command &&_cmd) {
			const auto token = _cmd.token;
			const auto _ = _cdb.register_command(_cmd);
		};

		/* help */
		{
			auto functor = [](State &state, [[maybe_unused]] std::string &&) -> bool {
				auto &proto = state.protocol();
				auto &db = state.command_db();
				proto.separator();
				proto.info("All registered commands ({}):", db.get_registry_map().size());
				for (const auto &cmd : db.get_registry_map()) {
					proto.info("\"{}\":", cmd.first);
					proto.info("\tDescription: \"{}\"", cmd.second.help);
					proto.info("\tRequires root: {}", cmd.second.requires_root);
				}
				return true;
			};

			reg(Command{
				.token = "help", .help = "Displays all registered commands with a short help message.", .functor = functor,
			});
		}

		/* config */
		{
			auto functor = [](State &state, [[maybe_unused]] std::string &&) -> bool {
				auto &proto = state.protocol();
				const auto &cfg = state.config();

				proto.separator();
				JsonStream stream;
				if (!cfg.serialize(stream)) {
					return false;
				}
				proto.info("Current system config:\n{}", stream.dump(4));

				return true;
			};

			reg(Command{.token = "cfg", .help = "Displays the current configuration as JSON.", .functor = functor,});
		}

		/* style */
		{
			auto functor = [ ]([[maybe_unused]] State &, std::string &&arg) -> bool {
				if (arg.starts_with("dark")) {
					gui::style_dark();
				}
				else if (arg.starts_with("light")) {
					gui::style_light();
				}
				else if (arg.starts_with("blue")) {
					gui::style_blue();
				}
				else if (arg.starts_with("cherry")) {
					gui::style_cherry();
				}
				else if (arg.starts_with("green")) {
					gui::style_green();
				}

				return true;
			};

			reg(Command{
				.token = "theme", .help = "Change the current theme of the system overlay.", .functor = functor
				, .requires_args = true,
			});
		}

		/* style_alpha */
		{
			auto functor = [ ]([[maybe_unused]] State &, std::string &&_arg) -> bool {
				float x = std::stof(_arg);

				if (x == .0f) {
					x = .1f;
				}

				gui::style_alpha_apply(x);

				return true;
			};

			reg(Command{
				.token = "alpha", .help = "Changes the transparency of the whole system overlay.", .functor = functor
				, .requires_args = true
			});
		}
	}
} // namespace dce // namespace dce
