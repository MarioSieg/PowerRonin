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

#pragma once

#include "../../include/dce/core/kernel.hpp"

#include "assembly.hpp"
#include "environment.hpp"
#include "static_class.hpp"
#include "static_method.hpp"

namespace dce::scripting {
	class Scripting final : public core::ISubsystem {
	public:
		/* Constructors, assignment operators, destructor */
		Scripting();
		Scripting(const Scripting&) = delete;
		Scripting(Scripting&&) = delete;
		auto operator=(const Scripting&) -> Scripting& = delete;
		auto operator=(Scripting&&) -> Scripting& = delete;
		~Scripting() override = default;

	private:
		/* Required kernel events */
		static constexpr auto EVENTS = core::ServiceEvents::ALL;

		/* Kernel events */
		virtual auto on_pre_startup([[maybe_unused]] Runtime& _rt) -> bool override;
		virtual auto on_post_startup([[maybe_unused]] Runtime& _rt) -> bool override;
		virtual auto on_pre_tick([[maybe_unused]] Runtime& _rt) -> bool override;
		virtual auto on_post_tick([[maybe_unused]] Runtime& _rt) -> bool override;
		virtual auto on_pre_shutdown([[maybe_unused]] Runtime& _rt) -> bool override;
		virtual auto on_post_shutdown([[maybe_unused]] Runtime& _rt) -> bool override;

		void setup_hooks();

		RuntimeEnvironment runtime_environment_ = {};
		Assembly core_assembly_ = {};

		/// <summary>
		/// Core class.
		/// </summary>
		struct {
			StaticClass klass = {};
			StaticMethod on_start = {};
			StaticMethod on_update = {};
			StaticMethod on_exit = {};
		} core_;

		/// <summary>
		/// Command database class.
		/// </summary>
		struct {
			StaticClass klass = {};
			StaticMethod on_command_enter = {}; // Called when command is enter to terminal.
		} command_db_;
	};
}
