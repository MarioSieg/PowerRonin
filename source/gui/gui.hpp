// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: gui.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "../../include/dce/core/kernel.hpp"
#include "../platform/input.hpp"
#include "../renderer/gui_renderer.hpp"

#include "gui_headers.hpp"
#include "terminal.hpp"
#include "editor.hpp"

namespace dce::gui {
	class Gui final : public core::ISubsystem {
	public:
		/* Constructors, assignment operators, destructor */
		Gui();
		Gui(const Gui&) = delete;
		Gui(Gui&&) = delete;
		auto operator=(const Gui&) -> Gui& = delete;
		auto operator=(Gui&&) -> Gui& = delete;
		~Gui() override = default;

	private:
		/* Required kernel events */
		static constexpr auto EVENTS = core::ServiceEvents::PRE_STARTUP | core::ServiceEvents::PRE_TICK | core::ServiceEvents::POST_TICK | core::ServiceEvents::PRE_SHUTDOWN;

		/* Kernel events */
		virtual auto on_pre_startup(State& /*state*/) -> bool override;
		virtual auto on_pre_tick(State& /*state*/) -> bool override;
		virtual auto on_post_tick(State& /*state*/) -> bool override;
		virtual auto on_pre_shutdown([[maybe_unused]] State&) -> bool override;

		void begin(std::uint16_t _width, std::uint16_t _height);
		void end() const;

		renderer::GuiRenderer gui_renderer_ = {};
		platform::GuiInput gui_input_ = {};
		ImGuiContext* gui_context_ = nullptr;
		ImPlotContext* plot_context_ = nullptr;
		Terminal terminal_ = {};
		bool show_terminal_ = false;
		Editor editor_ = {};
	};
} // namespace dce::gui // namespace dce::gui
