// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: editor.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 16.11.2020 11:55

#include "editor.hpp"
#include "gui_headers.hpp"
#include "font_headers.hpp"

#include "../../include/dce/state.hpp"

using namespace ImGui;

namespace dce::gui {

	void Editor::initialize(State &_state) {
		this->memory_editor_.OptShowDataPreview = true;
	}

	void Editor::update(State &_state, bool &_show_terminal) {
		[[likely]] if (this->show_menu_) {
			this->main_menu(_show_terminal);
		}

		[[likely]] if (this->show_hierarchy_viewer_) {
			this->hierarchy_.update(this->show_hierarchy_viewer_, _state.scenery().registry());
		}

		[[unlikely]] if (this->show_resource_viewer_) {
			this->resource_viewer_.update(this->show_resource_viewer_, _state.resource_manager());
		}

		[[unlikely]] if (this->show_profiler_) {
			this->profiler_.update(this->show_profiler_, _state.diagnostics(), _state.chrono());
		}

		[[unlikely]] if (this->show_shader_merger_) {
			this->shader_merger_.update(this->show_shader_merger_, _state.protocol());
		}

		[[likely]] if (this->show_inspector_) {
			this->inspector_.update(this->show_inspector_, _state.scenery().registry(), this->hierarchy_.get_selected());
		}

		[[unlikely]] if (this->memory_editor_.Open) {
			this->memory_editor_.DrawWindow(ICON_FA_MEMORY " Memory Editor", &_state, sizeof(State));
		}

	}

	void Editor::main_menu(bool &_show_terminal) {
		[[likely]] if (BeginMainMenuBar()) {
			[[unlikely]] if (BeginMenu("File")) {
				if (MenuItem("New")) {}
				if (MenuItem("Open")) {}
				if (MenuItem("Save")) {}
				if (MenuItem("Exit")) {}
				EndMenu();
			}
			[[unlikely]] if (BeginMenu("Tools")) {
				if (MenuItem(ICON_FA_TERMINAL " Terminal")) {
					_show_terminal = true;
				}
				if (MenuItem(ICON_FA_SITEMAP " Hierarchy")) {
					this->show_hierarchy_viewer_ = true;
				}
				if (MenuItem(ICON_FA_SLIDERS_H " Inspector")) {
					this->show_inspector_ = true;
				}
				if (MenuItem(ICON_FA_DATABASE " Resources")) {
					this->show_resource_viewer_ = true;
				}
				if (MenuItem(ICON_FA_CLOCK " Profiler")) {
					this->show_profiler_ = true;
				}
				if (MenuItem(ICON_FA_EYE " Shader Merger")) {
					this->show_shader_merger_ = true;
				}
				if (MenuItem(ICON_FA_SITEMAP " Hierarchy")) {
					this->show_hierarchy_viewer_ = true;
				}
				if (MenuItem(ICON_FA_MEMORY " Memory Editor")) {
					this->memory_editor_.Open = true;
				}
				EndMenu();
			}
			EndMainMenuBar();
		}
	}
}
