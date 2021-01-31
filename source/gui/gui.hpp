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

namespace PowerRonin::Interface
{
	class GuiSystem final : public Core::ISubsystem
	{
	public:
		/* Constructors, assignment operators, destructor */
		GuiSystem();
		GuiSystem(const GuiSystem&) = delete;
		GuiSystem(GuiSystem&&) = delete;
		auto operator=(const GuiSystem&) -> GuiSystem& = delete;
		auto operator=(GuiSystem&&) -> GuiSystem& = delete;
		~GuiSystem() override = default;

	private:
		/* Required kernel events */
		static constexpr auto EVENTS = Core::ServiceEvents::PreStartup | Core::ServiceEvents::PreTick |
			Core::ServiceEvents::PostTick | Core::ServiceEvents::PreShutdown;

		/* Kernel events */
		void OnPreStartup(Runtime&) override;
		void OnPreTick(Runtime&) override;
		void OnPostTick(Runtime&) override;
		void OnPreShutdown(Runtime&) override;

		void begin(std::uint16_t _width, std::uint16_t _height);
		void end() const;

		Renderer::GuiRenderer gui_renderer_ = {};
		Platform::GuiInput gui_input_ = {};
		ImGuiContext* gui_context_ = nullptr;
		ImPlotContext* plot_context_ = nullptr;
		Terminal terminal_ = {};

#if AUTO_TEC
		Editor editor_ = {};
#endif
	};
} // namespace PowerRonin::gui // namespace PowerRonin::gui
