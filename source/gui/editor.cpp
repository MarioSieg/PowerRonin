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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "editor.hpp"
#include "gui_headers.hpp"
#include "font_headers.hpp"
#include "window_names.hpp"
#include "../../include/dce/runtime.hpp"

using namespace ImGui;

namespace dce::gui {
	void Editor::initialize([[maybe_unused]] Runtime& _rt) {
		this->inspector_.initialize();
		this->memory_editor_.OptShowDataPreview = true;
	}

	void Editor::update(Runtime& _rt, bool& _show_terminal) {
		this->dockspace_id_ = DockSpaceOverViewport(GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

		[[unlikely]] if (this->first_use_) {
			this->default_layout();
			this->first_use_ = false;
		}

		[[likely]] if (this->show_menu_) {
			this->main_menu(_show_terminal);
		}

		[[likely]] if (this->show_hierarchy_viewer_) {
			this->hierarchy_.update(this->show_hierarchy_viewer_, _rt.scenery().registry());
		}

		[[unlikely]] if (this->show_resource_viewer_) {
			this->resource_viewer_.update(this->show_resource_viewer_, _rt.resource_manager());
		}

		[[unlikely]] if (this->show_profiler_) {
			this->profiler_.update(this->show_profiler_, _rt.diagnostics(), _rt.chrono());
		}

		[[likely]] if (this->show_inspector_) {
			this->inspector_.update(this->show_inspector_, _rt.scenery().registry(), _rt.resource_manager(), this->hierarchy_.get_selected());
		}

		[[unlikely]] if (this->memory_editor_.Open) {
			this->memory_editor_.DrawWindow(MEMORY_EDITOR_NAME, &_rt, sizeof(Runtime));
		}

		[[unlikely]] if (this->show_config_editor_) {
			this->config_editor_.update(this->show_config_editor_, _rt.config(), _rt.scenery().config);
		}
	}

	void Editor::main_menu(bool& _show_terminal) {
		[[likely]] if (BeginMainMenuBar()) {
			[[unlikely]] if (BeginMenu("File")) {
				if (MenuItem("New")) { }
				if (MenuItem("Open")) { }
				if (MenuItem("Save")) { }
				if (MenuItem("Exit")) { }
				EndMenu();
			}
			[[unlikely]] if (BeginMenu("Tools")) {
				if (MenuItem(ICON_FA_TERMINAL " Terminal")) {
					_show_terminal = true;
				}
				if (MenuItem(HIERARCHY_NAME)) {
					this->show_hierarchy_viewer_ = true;
				}
				if (MenuItem(INSPECTOR_NAME)) {
					this->show_inspector_ = true;
				}
				if (MenuItem(CONFIG_EDITOR_NAME)) {
					this->show_config_editor_ = true;
				}
				if (MenuItem(RESOURCE_VIEWER_NAME)) {
					this->show_resource_viewer_ = true;
				}
				if (MenuItem(PROFILER_NAME)) {
					this->show_profiler_ = true;
				}
				if (MenuItem(HIERARCHY_NAME)) {
					this->show_hierarchy_viewer_ = true;
				}
				if (MenuItem(MEMORY_EDITOR_NAME)) {
					this->memory_editor_.Open = true;
				}
				EndMenu();
			}
			EndMainMenuBar();
		}
	}

	void Editor::default_layout() const {
		DockBuilderRemoveNode(this->dockspace_id_);
		DockBuilderAddNode(this->dockspace_id_, ImGuiDockNodeFlags_DockSpace);
		DockBuilderSetNodeSize(this->dockspace_id_, GetMainViewport()->Size);
		auto main_id = this->dockspace_id_;

		const auto dock_id_left = DockBuilderSplitNode(main_id, ImGuiDir_Left, .20f, nullptr, &main_id);
		const auto dock_id_right = DockBuilderSplitNode(main_id, ImGuiDir_Right, .20f, nullptr, &main_id);
		const auto dock_id_bottom = DockBuilderSplitNode(main_id, ImGuiDir_Down, .20f, nullptr, &main_id);

		DockBuilderDockWindow(RESOURCE_VIEWER_NAME, dock_id_left);
		DockBuilderDockWindow(HIERARCHY_NAME, dock_id_left);

		DockBuilderDockWindow(CONFIG_EDITOR_NAME, dock_id_right);
		DockBuilderDockWindow(INSPECTOR_NAME, dock_id_right);

		DockBuilderDockWindow(TERMINAL_NAME, dock_id_bottom);
		DockBuilderDockWindow(PROFILER_NAME, dock_id_bottom);

		DockBuilderFinish(this->dockspace_id_);
	}
}
