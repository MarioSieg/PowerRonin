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

#include "../include/dce/cmddb.hpp"
#include "../include/dce/json_impl.hpp"
#include "../include/dce/runtime.hpp"
#include "gui/theme.hpp"
#include <string>

namespace dce {
	extern void register_common_commands(CmdDB&);

	auto CmdDB::analyze_and_call(Runtime& _rt, std::string&& _in) -> CommandExecutionResult {
		/* Add to history: */
		this->history_.push_back(_in);

		/* Search for existing command! */
		std::string_view command = "";
		for (const auto& [first, _] : this->commands_) {
			if (_in.starts_with(first)) {
				command = first;
				break;
			}
		}

		/* Command not found. */
		if (command == "") {
			return CommandExecutionResult::COMMAND_DOES_NOT_EXIST;
		}

		const auto& cmd = commands_[command];

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
		return cmd(_rt, std::move(_in)) ? CommandExecutionResult::OK : CommandExecutionResult::COMMAND_FUNCTOR_FAILED;
	}

	auto CmdDB::call(const std::string_view _command, Runtime& _rt, std::string&& _args) -> bool {
		if (!commands_.contains(_command)) {
			return false;
		}
		return commands_[_command](_rt, std::move(_args));
	}

	auto CmdDB::register_command(const Command& _command) -> bool {
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

	void register_common_commands(CmdDB& _cdb) {
		struct {
			CmdDB& db;

			inline void operator+=(const Command& _cmd) const {
				const auto _ = this->db.register_command(_cmd);
			}
		} registry = {_cdb};

		/* help */
		{
			auto functor = [](Runtime& _rt, [[maybe_unused]] std::string&&) -> bool {
				auto& proto = _rt.protocol();
				auto& db = _rt.command_db();
				proto.separator();
				proto.info("All registered commands ({}):", db.get_registry_map().size());
				for (const auto& [fst, snd] : db.get_registry_map()) {
					proto.info("\"{}\":", fst);
					proto.info("\tDescription: \"{}\"", snd.help);
					proto.info("\tRequires root: {}", snd.requires_root);
					proto.info("\tRequires args: {}", snd.requires_args);
				}
				return true;
			};

			registry += Command{
				.token = "help"
				, .help = "Displays all registered commands with a short help message."
				, .functor = +functor
				,
			};
		}

		/* config */
		{
			auto functor = [](Runtime& _rt, [[maybe_unused]] std::string&&) -> bool {
				auto& proto = _rt.protocol();
				const auto& cfg = _rt.config();

				proto.separator();
				JsonStream stream;
				try {
					cfg.serialize(stream);
				}
				catch (...) {}
				proto.info("Current system config:\n{}", stream.dump(4));

				return true;
			};

			registry += Command{.token = "cfg", .help = "Displays the current configuration as JSON.", .functor = +functor};
		}

		/* style */
		{
			auto functor = [ ]([[maybe_unused]] Runtime&, std::string&& _arg) -> bool {
				[[likely]] if (_arg.starts_with("dark")) {
					gui::style_dark();
				}
				else if (_arg.starts_with("light")) {
					gui::style_light();
				}
				else if (_arg.starts_with("blue")) {
					gui::style_blue();
				}
				else if (_arg.starts_with("cherry")) {
					gui::style_cherry();
				}
				else if (_arg.starts_with("green")) {
					gui::style_green();
				}

				return true;
			};

			registry += Command{
				.token = "theme"
				, .help = "Change the current theme of the system overlay."
				, .functor = +functor
				, .requires_args = true
				,
			};
		}

		/* style_alpha */
		{
			auto functor = [ ]([[maybe_unused]] Runtime&, std::string&& _arg) -> bool {
				float x = std::stof(_arg);

				[[unlikely]] if (x == .0f) {
					x = .1f;
				}

				gui::style_alpha_apply(x);

				return true;
			};

			registry += Command{
				.token = "alpha"
				, .help = "Changes transparency of the whole system overlay."
				, .functor = +functor
				, .requires_args = true
			};
		}

		/* entity report */
		{
			auto functor = [ ](Runtime& _rt, [[maybe_unused]] std::string&& _arg) -> bool {
				const auto& scene_registry = _rt.scenery().registry();
				auto& proto = _rt.protocol();
				proto.separator();
				proto.info("{} entities registered:", scene_registry.size());
				scene_registry.each([&](const ERef _entity) {
					proto.info("\t{:#08X}", _entity);
				});
				return true;
			};
			registry += Command{.token = "erep", .help = "Entity report.", .functor = functor,};
		}

		/* reload system resources */
		{
			auto functor = [ ](Runtime& _rt, [[maybe_unused]] std::string&& _args) -> bool {
				_rt.resource_manager().unload_all_resources();
				_rt.resource_manager().system_resources.load_all(_rt.resource_manager());
				return true;
			};
			registry += Command{.token = "rr", .help = "Reload system resources.", .functor = +functor};
		}
	}
} // namespace dce // namespace dce
