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

#include "../include/dce/runtime.hpp"

namespace dce {
	auto Runtime::protocol() & noexcept -> AsyncProtocol& {
		return this->protocol_;
	}

	auto Runtime::protocol() const & noexcept -> const AsyncProtocol& {
		return this->protocol_;
	}

	auto Runtime::config() & noexcept -> Config& {
		return this->config_;
	}

	auto Runtime::config() const & noexcept -> const Config& {
		return this->config_;
	}

	auto Runtime::class_db() & noexcept -> ClassDB& {
		return this->class_db_;
	}

	auto Runtime::class_db() const & noexcept -> const ClassDB& {
		return this->class_db_;
	}

	auto Runtime::command_db() & noexcept -> CmdDB& {
		return this->command_db_;
	}

	auto Runtime::command_db() const & noexcept -> const CmdDB& {
		return this->command_db_;
	}

	auto Runtime::resource_manager() & noexcept -> ResourceManager& {
		return this->resource_manager_;
	}

	auto Runtime::resource_manager() const & noexcept -> const ResourceManager& {
		return this->resource_manager_;
	}

	auto Runtime::diagnostics() const & noexcept -> const Diagnostics& {
		return this->diagnostics_;
	}

	auto Runtime::chrono() const & noexcept -> const Chrono& {
		return this->chrono_;
	}

	auto Runtime::scenery() const & noexcept -> const Scenery& {
		return this->scenery_;
	}

	auto Runtime::scenery() & noexcept -> Scenery& {
		return this->scenery_;
	}

	auto Runtime::input() const & noexcept -> const Input& {
		return this->input_;
	}

	auto Runtime::input() & noexcept -> Input& {
		return this->input_;
	}

	auto Runtime::render_data() const & noexcept -> const RenderData& {
		return this->render_data_;
	}

	auto Runtime::render_data() & noexcept -> RenderData& {
		return this->render_data_;
	}

	Runtime::Runtime()
		: protocol_(),
		  config_(),
		  class_db_(),
		  command_db_(),
		  resource_manager_(this->protocol_),
		  diagnostics_(),
		  chrono_(),
		  scenery_(),
		  input_(),
		  render_data_() { }

	void Runtime::initialize() {
		this->command_db_.install_common_commands();
		this->resource_manager_.system_resources.load_all(this->resource_manager_);
		this->scenery_.initialize();
		this->scenery_.new_default(this->resource_manager_);
	}

	void Runtime::shutdown() {
		this->scenery_.unload_all_entities();
		this->resource_manager_.unload_all_resources();
	}
} // namespace dce // namespace dce
