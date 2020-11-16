// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: editor.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 16.11.2020 11:54

#pragma once

#include "../../../include/dce/ecs.hpp"

#include "gui_headers.hpp"

#include "widgets/profiler.hpp"
#include "widgets/resource_viewer.hpp"
#include "widgets/shader_merger.hpp"
#include "widgets/hierarchy.hpp"
#include "widgets/inspector.hpp"

namespace dce::gui::widgets {
#include "widgets/ram_editor.hpp"
}

namespace dce {
	class State;

	namespace gui {
		class Editor final {
		public:
			void initialize(State &_state);
			void update(State &_state, bool &_show_terminal);
			void main_menu(bool &_show_terminal);

		private:
			/* Widgets: */
			widgets::ResourceViewer resource_viewer_ = {};
			widgets::Profiler profiler_ = {};
			widgets::ShaderMerger shader_merger_ = {};
			widgets::MemoryEditor memory_editor_ = {};
			widgets::Hierarchy hierarchy_ = {};
			widgets::Inspector inspector_ = {};

			bool show_menu_ = true;
			bool show_resource_viewer_ = false;
			bool show_profiler_ = false;
			bool show_shader_merger_ = false;
			bool show_hierarchy_viewer_ = false;
			bool show_inspector_ = false;
		};
	}
}
