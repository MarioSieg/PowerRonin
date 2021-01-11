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
#include "../platform/input.hpp"
#include "../renderer/gui_renderer.hpp"

#include "gui_headers.hpp"
#include "terminal.hpp"
#include "editor.hpp"

namespace power_ronin::gui
{
	class Gui final : public core::ISubsystem
	{
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
		static constexpr auto EVENTS = core::ServiceEvents::PRE_STARTUP | core::ServiceEvents::PRE_TICK |
			core::ServiceEvents::POST_TICK | core::ServiceEvents::PRE_SHUTDOWN;

		/* Kernel events */
		auto on_pre_startup(Runtime& /*state*/) -> bool override;
		auto on_pre_tick(Runtime& /*state*/) -> bool override;
		auto on_post_tick(Runtime& /*state*/) -> bool override;
		auto on_pre_shutdown([[maybe_unused]] Runtime&) -> bool override;

		void begin(std::uint16_t _width, std::uint16_t _height);
		void end() const;

		renderer::GuiRenderer gui_renderer_ = {};
		platform::GuiInput gui_input_ = {};
		ImGuiContext* gui_context_ = nullptr;
		ImPlotContext* plot_context_ = nullptr;
		Terminal terminal_ = {};

#if AUTO_TEC
		Editor editor_ = {};
#endif
	};
} // namespace power_ronin::gui // namespace power_ronin::gui
