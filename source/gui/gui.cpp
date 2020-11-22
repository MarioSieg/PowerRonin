// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: gui.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "gui.hpp"
#include "theme.hpp"

namespace dce::gui {
	Gui::Gui() : ISubsystem("OverlayGui", EVENTS) { }

	auto Gui::on_pre_startup(State& _state) -> bool {
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

		auto& cfg = _state.config().overlay;
		style_apply(cfg.style);
		style_antialiasing_apply(cfg.enable_antialiasing);
		style_alpha_apply(cfg.transparency);
		style_rounding_apply(cfg.rounding);

		[[unlikely]] if (!this->gui_input_.initialize()) {
			return false;
		}

		[[unlikely]] if (!this->gui_renderer_.initialize(_state.config().overlay.font_size)) {
			return false;
		}

		this->terminal_.initialize(_state.protocol().sink_to_terminal());
		this->editor_.initialize(_state);

		return true;
	}

	auto Gui::on_pre_tick(State& _state) -> bool {
		const auto width = _state.config().display.width;
		const auto height = _state.config().display.height;
		this->begin(width, height);
		return true;
	}

	auto Gui::on_post_tick(State& _state) -> bool {
		this->editor_.update(_state, this->show_terminal_);
		[[unlikely]] if (this->show_terminal_) {
			this->terminal_.update(this->show_terminal_, _state);
		}
		this->end();

		return true;
	}

	auto Gui::on_pre_shutdown([[maybe_unused]] State&) -> bool {
		this->gui_input_.shutdown();
		this->gui_renderer_.shutdown();
		return true;
	}

	void Gui::begin(const std::uint16_t _width, const std::uint16_t _height) {
		auto& io = ImGui::GetIO();
		io.DisplaySize = {static_cast<float>(_width), static_cast<float>(_height)};
		this->gui_input_.update();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
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
