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

#include "../include/dce/runtime.hpp"

namespace dce {

	Runtime::Runtime()
		: protocol_("native"),
		  scripting_protocol_("managed"),
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
		this->protocol_.get_logger()->flush();
		this->scripting_protocol_.get_logger()->flush();
	}
} // namespace dce // namespace dce
