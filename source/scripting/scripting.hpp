// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#pragma once

#include "../../include/power_ronin/core/kernel.hpp"

#include "assembly.hpp"
#include "environment.hpp"
#include "static_class.hpp"
#include "static_method.hpp"

namespace PowerRonin::Scripting
{
	class ScriptingSystem final : public Core::ISubsystem
	{
	public:
		/* Constructors, assignment operators, destructor */
		ScriptingSystem();
		ScriptingSystem(const ScriptingSystem&) = delete;
		ScriptingSystem(ScriptingSystem&&) = delete;
		auto operator=(const ScriptingSystem&) -> ScriptingSystem& = delete;
		auto operator=(ScriptingSystem&&) -> ScriptingSystem& = delete;
		~ScriptingSystem() override = default;

	private:
		/* Required kernel events */
		static constexpr auto EVENTS = Core::ServiceEvents::All;

		/* Kernel events */
		void OnPreStartup(Runtime&) override;
		void OnPostStartup(Runtime&) override;
		void OnPreTick(Runtime&) override;
		void OnPostTick(Runtime&) override;
		void OnPreShutdown(Runtime&) override;
		void OnPostShutdown(Runtime&) override;

		void setup_hooks();

		RuntimeEnvironment runtime_environment_ = {};
		Assembly core_assembly_ = {};

		/// <summary>
		/// Core class.
		/// </summary>
		struct
		{
			StaticClass klass = {};

			StaticMethod on_pre_startup = {};
			StaticMethod on_post_startup = {};

			StaticMethod on_pre_tick = {};
			StaticMethod on_post_tick = {};

			StaticMethod on_pre_shutdown = {};
			StaticMethod on_post_shutdown = {};
		} core_;

		/// <summary>
		/// Command database class.
		/// </summary>
		struct
		{
			StaticClass klass = {};
			StaticMethod on_command_enter = {}; // Called when command is enter to terminal.
		} command_db_;
	};
}
