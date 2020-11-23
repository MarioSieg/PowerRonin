// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: state.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

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
	class State final : public IEventBehaviour {
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

		State() = default;
		State(const State&) = delete;
		State(State&&) noexcept = delete;
		auto operator=(const State&) -> State& = delete;
		auto operator=(State&&) noexcept -> State& = delete;
		virtual ~State() override = default;

		virtual void start() override;
		virtual void update() override;
		virtual void end() override;

	private:
		AsyncProtocol protocol_ = {};
		Config config_ = {};
		ClassDB class_db_ = {};
		CmdDB command_db_ = {};
		ResourceManager importeur_ = {};
		Diagnostics diagnostics_ = {};
		Chrono chrono_ = {};
		Scenery scenery_ = {};
		Input input_ = {};
	};
} // namespace dce // namespace dce
