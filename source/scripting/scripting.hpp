#pragma once

#include "../../Include/PowerRonin/core/Kernel.hpp"

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
		virtual void OnPreStartup(Runtime&) override;
		virtual void OnPostStartup(Runtime&) override;
		virtual void OnPreTick(Runtime&) override;
		virtual void OnPostTick(Runtime&) override;
		virtual void OnPreShutdown(Runtime&) override;
		virtual void OnPostShutdown(Runtime&) override;

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
