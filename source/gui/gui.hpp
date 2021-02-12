#pragma once

#include "../../Include/PowerRonin/core/Kernel.hpp"
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
		virtual void OnPreStartup(Runtime&) override;
		virtual void OnPreTick(Runtime&) override;
		virtual void OnPostTick(Runtime&) override;
		virtual void OnPreShutdown(Runtime&) override;

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
