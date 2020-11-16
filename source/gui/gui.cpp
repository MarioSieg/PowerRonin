// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: gui.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "gui.hpp"
#include "dockspace.hpp"
#include "theme.hpp"
#include "font_headers.hpp"
#include "../../include/dce/core/publish.hpp"

namespace dce::gui {
	Gui::Gui() : ISubsystem("OverlayGui", EVENTS) { }

	auto Gui::on_pre_startup(State &_state) -> bool {
		this->gui_context_ = ImGui::CreateContext();
		[[unlikely]] if (this->gui_context_ == nullptr) {
			return false;
		}

		this->plot_context_ = ImPlot::CreateContext();
		[[unlikely]] if (this->plot_context_ == nullptr) {
			return false;
		}

		auto &io = ImGui::GetIO();
		io.IniFilename = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		auto &cfg = _state.config().overlay;
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

		this->memory_editor_.OptShowDataPreview = true;

		return this->terminal_.initialize(_state.protocol().sink_to_terminal());
	}

	auto Gui::on_pre_tick(State &_state) -> bool {
		const auto width = _state.config().display.width;
		const auto height = _state.config().display.height;
		this->begin(width, height);
		return true;
	}

	auto Gui::on_post_tick(State &_state) -> bool {
		if constexpr (!IS_PUBLISHED) {
			[[likely]] if (this->show_menu_) {
				this->main_menu();
			}

			[[likely]] if (this->show_resource_viewer_) {
				this->resource_viewer_.update(this->show_resource_viewer_, _state.importeur());
			}

			[[likely]] if (this->show_profiler_) {
				this->profiler_.update(this->show_profiler_, _state.diagnostics(), _state.chrono());
			}

			[[likely]] if (this->show_shader_merger_) {
				this->shader_merger_.update(this->show_shader_merger_, _state.protocol());
			}

			[[likely]] if (this->memory_editor_.Open) {
				this->memory_editor_.DrawWindow(ICON_FA_MEMORY " Memory Editor", &_state, sizeof(State));
			}
		}

		[[unlikely]] if (this->show_terminal_) {
			this->terminal_.update(this->show_terminal_, _state);
		}

		this->end();

		return true;
	}

	auto Gui::on_pre_shutdown([[maybe_unused]] State &) -> bool {
		this->gui_input_.shutdown();
		this->gui_renderer_.shutdown();
		return true;
	}

	void Gui::begin(const std::uint16_t _width, const std::uint16_t _height) {
		auto &io = ImGui::GetIO();
		io.DisplaySize = {static_cast<float>(_width), static_cast<float>(_height)};
		this->gui_input_.update();
		ImGui::NewFrame();
		if constexpr (!IS_PUBLISHED) {
			//begin_dockspace();
		}
	}

	void Gui::end() const {
		if constexpr (!IS_PUBLISHED) {
			//end_dockspace();
		}
		ImGui::EndFrame();
		ImGui::Render();
		const ImDrawData *const data = ImGui::GetDrawData();
		[[unlikely]] if (data != nullptr) {
			this->gui_renderer_.render(data);
		}
	}

	void Gui::main_menu() {
		using namespace ImGui;
		[[likely]] if (BeginMainMenuBar()) {
			[[unlikely]] if (BeginMenu("File")) {
				if (MenuItem("New")) {}
				if (MenuItem("Open")) {}
				if (MenuItem("Save")) {}
				if (MenuItem("Exit")) {}
				EndMenu();
			}
			[[unlikely]] if (BeginMenu("Tools")) {
				[[unlikely]] if (MenuItem(ICON_FA_TERMINAL " Terminal")) {
					this->show_terminal_ = true;
				}
				[[unlikely]] if (MenuItem(ICON_FA_DATABASE " Resources")) {
					this->show_resource_viewer_ = true;
				}
				[[unlikely]] if (MenuItem(ICON_FA_CLOCK " Profiler")) {
					this->show_profiler_ = true;
				}
				[[unlikely]] if (MenuItem(ICON_FA_EYE " Shader Merger")) {
					this->show_shader_merger_ = true;
				}
				[[unlikely]] if (MenuItem(ICON_FA_MEMORY " Memory Editor")) {
					this->memory_editor_.Open = true;
				}
				EndMenu();
			}
			EndMainMenuBar();
		}
	}
} // namespace dce::gui // namespace dce::gui
