#include "../include/dce/runtime.hpp"
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

namespace dce
{
	Runtime::Runtime() : protocol_("native"),
	                     scripting_protocol_("managed"),
	                     config_(),
	                     class_db_(),
	                     resource_manager_(this->protocol_),
	                     diagnostics_(),
	                     chrono_(),
	                     scenery_(),
	                     input_(),
	                     render_data_(),
	                     terminal_hook_(nullptr) { }

	void Runtime::initialize()
	{
		this->resource_manager_.system_resources.load_all(this->resource_manager_);
		this->scenery_.initialize();
		this->scenery_.new_default(this->resource_manager_);
	}

	void Runtime::shutdown()
	{
		this->scenery_.unload_all_entities();
		this->resource_manager_.unload_all_resources();
		this->protocol_.get_logger()->flush();
		this->scripting_protocol_.get_logger()->flush();
	}

	auto Runtime::protocol() & noexcept -> AsyncProtocol&
	{
		return this->protocol_;
	}

	auto Runtime::protocol() const & noexcept -> const AsyncProtocol&
	{
		return this->protocol_;
	}

	auto Runtime::config() & noexcept -> Config&
	{
		return this->config_;
	}

	auto Runtime::config() const & noexcept -> const Config&
	{
		return this->config_;
	}

	auto Runtime::class_db() & noexcept -> ClassDB&
	{
		return this->class_db_;
	}

	auto Runtime::class_db() const & noexcept -> const ClassDB&
	{
		return this->class_db_;
	}

	auto Runtime::resource_manager() & noexcept -> ResourceManager&
	{
		return this->resource_manager_;
	}

	auto Runtime::resource_manager() const & noexcept -> const ResourceManager&
	{
		return this->resource_manager_;
	}

	auto Runtime::diagnostics() const & noexcept -> const Diagnostics&
	{
		return this->diagnostics_;
	}

	auto Runtime::chrono() const & noexcept -> const Chrono&
	{
		return this->chrono_;
	}

	auto Runtime::scenery() const & noexcept -> const Scenery&
	{
		return this->scenery_;
	}

	auto Runtime::scenery() & noexcept -> Scenery&
	{
		return this->scenery_;
	}

	auto Runtime::input() const & noexcept -> const Input&
	{
		return this->input_;
	}

	auto Runtime::render_data() const & noexcept -> const RenderData&
	{
		return this->render_data_;
	}

	auto Runtime::render_data() & noexcept -> RenderData&
	{
		return this->render_data_;
	}

	auto Runtime::scripting_protocol() const & noexcept -> const AsyncProtocol&
	{
		return this->scripting_protocol_;
	}

	auto Runtime::scripting_protocol() & noexcept -> AsyncProtocol&
	{
		return this->scripting_protocol_;
	}

	auto Runtime::terminal_hook() const & noexcept -> const std::function<void(char*)>&
	{
		return this->terminal_hook_;
	}

	auto Runtime::terminal_hook() & noexcept -> std::function<void(char*)>&
	{
		return this->terminal_hook_;
	}
} // namespace dce // namespace dce
