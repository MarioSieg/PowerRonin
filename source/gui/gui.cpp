// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "gui.hpp"
#include "theme.hpp"

namespace dce::gui {
	Gui::Gui() : ISubsystem("OverlayGui", EVENTS) { }

	auto Gui::on_pre_startup(Runtime& _rt) -> bool {
		this->gui_context_ = ImGui::CreateContext();
		[[unlikely]] if (this->gui_context_ == nullptr) {
			return false;
		}

		this->plot_context_ = ImPlot::CreateContext();
		[[unlikely]] if (this->plot_context_ == nullptr) {
			return false;
		}

		auto& io = ImGui::GetIO();
		io.IniFilename = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.MouseDrawCursor = true;

		auto& cfg = _rt.config().overlay;
		style_apply(cfg.theme);
		style_antialiasing_apply(cfg.enable_anti_aliasing);
		style_alpha_apply(cfg.alpha);
		style_rounding_apply(cfg.rounding);

		[[unlikely]] if (!this->gui_input_.initialize()) {
			return false;
		}

		[[unlikely]] if (!this->gui_renderer_.initialize(_rt.config().overlay.font_size)) {
			return false;
		}

		this->terminal_.initialize(_rt.protocol(), _rt.scripting_protocol());
		this->editor_.initialize(_rt);

		return true;
	}

	auto Gui::on_pre_tick(Runtime& _rt) -> bool {
		const auto width = _rt.config().display.width;
		const auto height = _rt.config().display.height;
		this->begin(width, height);
		return true;
	}

	auto Gui::on_post_tick(Runtime& _rt) -> bool {
		this->editor_.update(_rt, _rt.config().overlay.show_terminal);
		[[unlikely]] if (_rt.input().is_key_down(Key::GRAVE_ACCENT)) {
			_rt.config().overlay.show_terminal = true;
		}
		[[unlikely]] if (_rt.config().overlay.show_terminal) {
			this->terminal_.update(_rt.config().overlay.show_terminal, _rt);
		}
		this->end();

		return true;
	}

	auto Gui::on_pre_shutdown([[maybe_unused]] Runtime&) -> bool {
		this->gui_input_.shutdown();
		this->gui_renderer_.shutdown();
		return true;
	}

	void Gui::begin(const std::uint16_t _width, const std::uint16_t _height) {
		this->gui_input_.update();
		ImGui::NewFrame();
	}

	void Gui::end() const {
		ImGui::EndFrame();
		ImGui::Render();
		const ImDrawData* const data = ImGui::GetDrawData();
		[[unlikely]] if (data != nullptr) {
			this->gui_renderer_.render(data);
		}
	}
} // namespace dce::gui // namespace dce::gui
