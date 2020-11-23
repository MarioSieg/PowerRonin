// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: scripting.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 23.11.2020 10:01

#pragma once

#include "../../include/dce/core/kernel.hpp"

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
		virtual auto on_pre_startup([[maybe_unused]] State& _state) -> bool override;
		virtual auto on_post_startup([[maybe_unused]] State& _state) -> bool override;
		virtual auto on_pre_tick([[maybe_unused]] State& _state) -> bool override;
		virtual auto on_post_tick([[maybe_unused]] State& _state) -> bool override;
		virtual auto on_pre_shutdown([[maybe_unused]] State& _state) -> bool override;
		virtual auto on_post_shutdown([[maybe_unused]] State& _state) -> bool override;
	};
}
