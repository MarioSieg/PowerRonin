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

#pragma once

#include "gui_headers.hpp"

#include "widgets/profiler.hpp"
#include "widgets/resource_viewer.hpp"
#include "widgets/hierarchy.hpp"
#include "widgets/inspector.hpp"
#include "widgets/config_editor.hpp"
#include "widgets/scenery_viewer.hpp"

namespace dce::gui::widgets {
#include "widgets/ram_editor.hpp"
}

namespace dce {
	class Runtime;

	namespace gui {
		class Editor final {
		public:
			void initialize(Runtime& _rt);
			void update(Runtime& _rt, bool& _show_terminal);
			void main_menu(Runtime& _rt, bool& _show_terminal);

		private:
			void default_layout() const;

			/* Widgets: */
			widgets::ResourceViewer resource_viewer_ = {};
			widgets::Profiler profiler_ = {};
			widgets::MemoryEditor memory_editor_ = {};
			widgets::Hierarchy hierarchy_ = {};
			widgets::Inspector inspector_ = {};
			widgets::ConfigEditor config_editor_ = {};
			widgets::SceneryViewer scenery_viewer_ = {};

			bool show_menu_ = true;
			bool show_resource_viewer_ = true;
			bool show_profiler_ = true;
			bool show_hierarchy_viewer_ = true;
			bool show_inspector_ = true;
			bool show_config_editor_ = true;
			bool show_scenery_viewer_ = true;

			bool first_use_ = true;
			ImGuiID dockspace_id_ = 0;
		};
	}
}
