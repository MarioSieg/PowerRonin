#pragma once

#if AUTO_TEC

#include "gui_headers.hpp"

#include "widgets/profiler.hpp"
#include "widgets/resource_viewer.hpp"
#include "widgets/hierarchy.hpp"
#include "widgets/inspector.hpp"
#include "widgets/config_editor.hpp"
#include "widgets/scenery_viewer.hpp"

namespace PowerRonin::Interface::widgets
{
#include "widgets/ram_editor.hpp"
}

namespace PowerRonin
{
	class Runtime;

	namespace Interface
	{
		class Editor final
		{
		public:
			void initialize(Runtime& _rt);
			void update(Runtime& _rt, bool& _show_terminal);

		private:
			void default_layout() const;
			void main_menu(Runtime& _rt, bool& _show_terminal);
			void render_manipulator_gizmos(Transform* const _transform, RenderState& _data, const SystemConfig& _config) const noexcept;

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
			ImGuizmo::MODE gizmo_mode_ = ImGuizmo::WORLD;
			ImGuizmo::OPERATION gizmo_op_ = ImGuizmo::OPERATION::TRANSLATE;
		};
	}
}

#endif
