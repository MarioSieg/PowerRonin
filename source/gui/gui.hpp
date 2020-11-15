// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: gui.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#pragma once

#include "../../include/dce/core/kernel.hpp"
#include "../platform/imgui_input.hpp"
#include "../renderer/imgui_renderer.hpp"

#include "widgets/profiler.hpp"
#include "widgets/resource_viewer.hpp"
#include "widgets/terminal.hpp"
#include "widgets/shader_merger.hpp"

#include "imgui_headers.hpp"
#include "ram_editor.hpp"

namespace dce::gui {
	class Gui final : public core::ISubsystem {
	public:
		/* Constructors, assignment operators, destructor */
		Gui();
		Gui(const Gui &) = delete;
		Gui(Gui &&) = delete;
		auto operator=(const Gui &) -> Gui& = delete;
		auto operator=(Gui &&) -> Gui& = delete;
		~Gui() override = default;

	private:
		/* Required kernel events */
		static constexpr auto EVENTS = core::ServiceEvents::PRE_STARTUP | core::ServiceEvents::PRE_TICK |
			core::ServiceEvents::POST_TICK | core::ServiceEvents::PRE_SHUTDOWN;

		/* Kernel events */
		virtual auto on_pre_startup(State & /*state*/) -> bool override;
		virtual auto on_pre_tick(State & /*state*/) -> bool override;
		virtual auto on_post_tick(State & /*state*/) -> bool override;
		virtual auto on_pre_shutdown([[maybe_unused]] State &) -> bool override;

		void begin(std::uint16_t _width, std::uint16_t _height);
		void end() const;
		void main_menu();

		renderer::GuiRenderer gui_renderer_ = {};
		platform::GuiInput gui_input_ = {};
		ImGuiContext *gui_context_ = nullptr;
		ImPlotContext *plot_context_ = nullptr;

		/* Widgets: */
		widgets::Terminal terminal_ = {};
		widgets::ResourceViewer resource_viewer_ = {};
		widgets::Profiler profiler_ = {};
		widgets::ShaderMerger shader_merger_ = {};
		MemoryEditor memory_editor_ = {};

		bool show_menu_ = true;
		bool show_terminal_ = false;
		bool show_resource_viewer_ = false;
		bool show_profiler_ = false;
		bool show_shader_merger_ = false;
	};
} // namespace dce::gui // namespace dce::gui
