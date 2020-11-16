// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: state.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "../include/dce/state.hpp"

namespace dce {
	auto State::protocol() & noexcept -> AsyncProtocol& {
		return this->protocol_;
	}

	auto State::protocol() const & noexcept -> const AsyncProtocol& {
		return this->protocol_;
	}

	auto State::config() & noexcept -> Config& {
		return this->config_;
	}

	auto State::config() const & noexcept -> const Config& {
		return this->config_;
	}

	auto State::class_db() & noexcept -> ClassDB& {
		return this->class_db_;
	}

	auto State::class_db() const & noexcept -> const ClassDB& {
		return this->class_db_;
	}

	auto State::command_db() & noexcept -> CmdDB& {
		return this->command_db_;
	}

	auto State::command_db() const & noexcept -> const CmdDB& {
		return this->command_db_;
	}

	auto State::resource_manager() & noexcept -> ResourceManager& {
		return this->importeur_;
	}

	auto State::resource_manager() const & noexcept -> const ResourceManager& {
		return this->importeur_;
	}

	auto State::diagnostics() const & noexcept -> const Diagnostics& {
		return this->diagnostics_;
	}

	auto State::chrono() const & noexcept -> const Chrono& {
		return this->chrono_;
	}

	auto State::scenery() const & noexcept -> const Scenery& {
		return this->scenery_;
	}

	auto State::scenery() & noexcept -> Scenery& {
		return this->scenery_;
	}

	void State::start() {
		this->command_db_.install_common_commands();
		this->importeur_.load_system_resources();
		this->scenery_.initialize();
		this->scenery_.new_default(this->importeur_);
	}

	void State::update() { }

	void State::end() { }
} // namespace dce // namespace dce
