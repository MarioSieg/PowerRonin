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

#include "gui.hpp"
#include "theme.hpp"

namespace PowerRonin::Interface
{
	GuiSystem::GuiSystem() : ISubsystem("OverlayGui", EVENTS) { }

	void GuiSystem::OnPreStartup(Runtime& runtime)
	{
		this->gui_context_ = ImGui::CreateContext();
		if (this->gui_context_ == nullptr) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to create gui context!");
		}

		this->plot_context_ = ImPlot::CreateContext();
		if (this->plot_context_ == nullptr) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to create plot context!");
		}

		auto& io = ImGui::GetIO();
		io.IniFilename = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.MouseDrawCursor = true;

		auto& cfg = runtime.Config().Editor;
		style_apply(SystemTheme::DARK);
		style_antialiasing_apply(cfg.EnableFontAntiAliasing);
		style_alpha_apply(cfg.Alpha);
		style_rounding_apply(cfg.Rounding);

		if (cfg.EnableAutoFontSize) [[likely]]
		{
			const auto w = runtime.Config().Display.Resolution.Width;
			const auto h = runtime.Config().Display.Resolution.Height;
			if (w <= 2560 && h <= 1440) [[unlikely]]
			{
				cfg.CustomFontSize = cfg.AutoFontSizeWideQuadHD;
			}
			else if (w <= 3840 && h <= 2160) [[unlikely]]
			{
				cfg.CustomFontSize = cfg.AutoFontSizeUltraHD;
			}
			else
			{
				cfg.CustomFontSize = cfg.AutoFontSizeFullHD;
			}
		}

		cfg.CustomFontSize = std::clamp<decltype(cfg.CustomFontSize)>(cfg.CustomFontSize, 10, 28);

		if (!this->gui_input_.initialize()) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to initialize input!");
		}

		if (!this->gui_renderer_.initialize(runtime.Config().Editor.CustomFontSize)) [[unlikely]]
		{
				throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to initialize gui renderer!");
		}

		this->terminal_.initialize(runtime.Protocol(), runtime.ScriptingProtocol());

#if AUTO_TEC
		this->editor_.initialize(runtime);
#endif
	}

	void GuiSystem::OnPreTick(Runtime& runtime)
	{
		const auto width = runtime.Config().Display.Resolution.Width;
		const auto height = runtime.Config().Display.Resolution.Height;
		this->begin(static_cast<std::uint16_t>(width), static_cast<std::uint16_t>(height));
	}

	void GuiSystem::OnPostTick(Runtime& runtime)
	{
#if AUTO_TEC
		this->editor_.update(runtime, runtime.Config().Editor.ShowTerminal);
		if (runtime.Input().IsKeyDown(Key::GraveAccent)) [[unlikely]]
		{
			runtime.Config().Editor.ShowTerminal = true;
		}
		if (runtime.Config().Editor.ShowTerminal) [[unlikely]]
		{
			this->terminal_.update(runtime.Config().Editor.ShowTerminal, runtime);
		}
		this->end();
#endif
	}

	void GuiSystem::OnPreShutdown(Runtime&)
	{
		this->gui_input_.shutdown();
		this->gui_renderer_.shutdown();
	}

	void GuiSystem::begin(const std::uint16_t _width, const std::uint16_t _height)
	{
		this->gui_input_.update();
		ImGui::NewFrame();
	}

	void GuiSystem::end() const
	{
		ImGui::EndFrame();
#if AUTO_TEC
		ImGui::Render();
		if (const ImDrawData* const data = ImGui::GetDrawData(); data) [[likely]]
		{
			this->gui_renderer_.render(data);
		}
#endif
	}
} // namespace PowerRonin::gui // namespace PowerRonin::gui
