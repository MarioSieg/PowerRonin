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

#include "classdb.hpp"
#include "cmddb.hpp"
#include "config.hpp"
#include "diagnostics.hpp"
#include "event_behaviour.hpp"
#include "resource_manager.hpp"
#include "proto.hpp"
#include "chrono.hpp"
#include "scenery.hpp"
#include "input.hpp"

namespace dce {
	/* Contains all system states and data. */
	class Runtime final {
	public:
		[[nodiscard]] auto protocol() & noexcept -> AsyncProtocol&;

		[[nodiscard]] auto protocol() const & noexcept -> const AsyncProtocol&;

		[[nodiscard]] auto config() & noexcept -> Config&;

		[[nodiscard]] auto config() const & noexcept -> const Config&;

		[[nodiscard]] auto class_db() & noexcept -> ClassDB&;

		[[nodiscard]] auto class_db() const & noexcept -> const ClassDB&;

		[[nodiscard]] auto command_db() & noexcept -> CmdDB&;

		[[nodiscard]] auto command_db() const & noexcept -> const CmdDB&;

		[[nodiscard]] auto resource_manager() & noexcept -> ResourceManager&;

		[[nodiscard]] auto resource_manager() const & noexcept -> const ResourceManager&;

		[[nodiscard]] auto diagnostics() const & noexcept -> const Diagnostics&;

		[[nodiscard]] auto chrono() const & noexcept -> const Chrono&;

		[[nodiscard]] auto scenery() const & noexcept -> const Scenery&;

		[[nodiscard]] auto scenery() & noexcept -> Scenery&;

		[[nodiscard]] auto input() const & noexcept -> const Input&;

		[[nodiscard]] auto input() & noexcept -> Input&;

		Runtime() = default;
		Runtime(const Runtime&) = delete;
		Runtime(Runtime&&) noexcept = delete;
		auto operator=(const Runtime&) -> Runtime& = delete;
		auto operator=(Runtime&&) noexcept -> Runtime& = delete;
		~Runtime() = default;

		void initialize();
		void shutdown();

	private:
		AsyncProtocol protocol_ = {};
		Config config_ = {};
		ClassDB class_db_ = {};
		CmdDB command_db_ = {};
		ResourceManager resource_manager_ = {};
		Diagnostics diagnostics_ = {};
		Chrono chrono_ = {};
		Scenery scenery_ = {};
		Input input_ = {};
	};
} // namespace dce // namespace dce
