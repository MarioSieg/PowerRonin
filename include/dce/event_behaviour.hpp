// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: event_behaviour.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

namespace dce {
	class IEventBehaviour {
	public:
		IEventBehaviour() noexcept = default;
		IEventBehaviour(const IEventBehaviour&) noexcept = default;
		IEventBehaviour(IEventBehaviour&&) noexcept = default;
		auto operator=(const IEventBehaviour&) noexcept -> IEventBehaviour& = default ;
		auto operator=(IEventBehaviour&&) noexcept -> IEventBehaviour& = default;
		virtual ~IEventBehaviour() = default;

		virtual void start();
		virtual void update();
		virtual void end();
	};
} // namespace dce // namespace dce
