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

#if AUTO_TEC

#include "editor.hpp"
#include "gui_headers.hpp"
#include "font_headers.hpp"
#include "window_names.hpp"
#include "../../include/power_ronin/runtime.hpp"

using namespace ImGui;

namespace power_ronin::gui
{
	void Editor::initialize([[maybe_unused]] Runtime& _rt)
	{
		this->inspector_.initialize();
		this->memory_editor_.OptShowDataPreview = true;
	}

	void Editor::update(Runtime& _rt, bool& _show_terminal)
	{
		SetNextWindowBgAlpha(.0F);
		this->dockspace_id_ = DockSpaceOverViewport(nullptr);

		if (this->first_use_) [[unlikely]]
		{
			this->default_layout();
			this->first_use_ = false;
		}

		if (this->show_menu_) [[likely]]
		{
			this->main_menu(_rt, _show_terminal);
		}

		if (this->show_hierarchy_viewer_) [[likely]]
		{
			this->hierarchy_.update(this->show_hierarchy_viewer_, _rt.scenery().registry());
		}

		if (this->show_resource_viewer_) [[unlikely]]
		{
			this->resource_viewer_.update(this->show_resource_viewer_, _rt.resource_manager());
		}

		if (this->show_profiler_) [[unlikely]]
		{
			this->profiler_.update(this->show_profiler_, _rt.diagnostics(), _rt.chrono());
		}

		if (this->show_inspector_) [[likely]]
		{
			this->inspector_.update(this->show_inspector_, this->hierarchy_.selected, _rt);
		}

		if (this->memory_editor_.Open) [[unlikely]]
		{
			this->memory_editor_.DrawWindow(MEMORY_EDITOR_NAME, &_rt, sizeof(Runtime));
		}

		if (this->show_config_editor_) [[unlikely]]
		{
			this->config_editor_.update(this->show_config_editor_, _rt.config(), _rt.scenery().config);
		}

		if (this->show_scenery_viewer_) [[likely]]
		{
			this->scenery_viewer_.update(this->show_scenery_viewer_, _rt.render_data());
		}

		if(!_rt.is_playing()) [[likely]]
		{
			const auto selected_entity = this->hierarchy_.selected;
			auto& registry = _rt.scenery().registry();

			this->render_manipulator_gizmos(registry.valid(selected_entity) 
				&& registry.has<Transform>(selected_entity) 
				? &registry.get<Transform>(selected_entity) : nullptr, 
				_rt.render_data(),_rt.config());
		}
	}

	void Editor::main_menu(Runtime& _rt, bool& _show_terminal)
	{
		if (BeginMainMenuBar()) [[likely]]
		{
			if (BeginMenu("File")) [[unlikely]]
			{
				if (MenuItem("New")) { }
				if (MenuItem("Open")) { }
				if (MenuItem("Save")) { }
				if (MenuItem("Exit")) { }
				EndMenu();
			}
			if (BeginMenu("Entity")) [[unlikely]]
			{
				auto& reg = _rt.scenery().registry();
				if (MenuItem("Create New"))
				{
					const auto new_entity = reg.create();
					reg.emplace<MetaData>(new_entity).name = "New Entity " + std::to_string(++this->hierarchy_.entity_counter);
					reg.emplace<Transform>(new_entity);
					this->hierarchy_.selected = new_entity;
				}
				if (MenuItem("Create Container"))
				{
					const auto new_entity = reg.create();
					reg.emplace<MetaData>(new_entity).name = "New Entity " + std::to_string(++this->hierarchy_.entity_counter);
				}
				if (MenuItem("Delete Selected"))
				{
					reg.destroy(this->hierarchy_.selected);
					if (reg.valid(static_cast<ERef>(static_cast<std::uint64_t>(this->hierarchy_.selected) + 1)))
					{
						this->hierarchy_.selected = static_cast<ERef>(static_cast<std::uint64_t>(this->hierarchy_.selected) + 1);
					}
				}
				if (MenuItem("Delete All"))
				{
					reg.clear();
				}
				EndMenu();
			}
			if (BeginMenu("Tools")) [[unlikely]]
			{
				if (MenuItem(ICON_FA_TERMINAL " Terminal"))
				{
					_show_terminal = true;
				}
				if (MenuItem(HIERARCHY_NAME))
				{
					this->show_hierarchy_viewer_ = true;
				}
				if (MenuItem(INSPECTOR_NAME))
				{
					this->show_inspector_ = true;
				}
				if (MenuItem(SCENERY_VIEWER_NAME))
				{
					this->show_scenery_viewer_ = true;
				}
				if (MenuItem(CONFIG_EDITOR_NAME))
				{
					this->show_config_editor_ = true;
				}
				if (MenuItem(RESOURCE_VIEWER_NAME))
				{
					this->show_resource_viewer_ = true;
				}
				if (MenuItem(PROFILER_NAME))
				{
					this->show_profiler_ = true;
				}
				if (MenuItem(HIERARCHY_NAME))
				{
					this->show_hierarchy_viewer_ = true;
				}
				if (MenuItem(MEMORY_EDITOR_NAME))
				{
					this->memory_editor_.Open = true;
				}
				EndMenu();
			}
			PushStyleColor(ImGuiCol_Button, 0x00000000);
			Separator();

			if (Button(ICON_FA_HAND_ROCK)) [[unlikely]]
			{
				this->gizmo_op_ = ImGuizmo::OPERATION::BOUNDS;
			}

			if (IsItemHovered()) [[unlikely]]
			{
				BeginTooltip();
				TextUnformatted("Edit bounds of selected object");
				EndTooltip();
			}

			if (Button(ICON_FA_ARROWS)) [[unlikely]]
			{
				this->gizmo_op_ = ImGuizmo::OPERATION::TRANSLATE;
			}

			if (IsItemHovered()) [[unlikely]]
			{
				BeginTooltip();
				TextUnformatted("Edit position of selected object");
				EndTooltip();
			}

			if (Button(ICON_FA_SYNC)) [[unlikely]]
			{
				this->gizmo_op_ = ImGuizmo::OPERATION::ROTATE;
			}

			if (IsItemHovered()) [[unlikely]]
			{
				BeginTooltip();
				TextUnformatted("Edit rotation of selected object");
				EndTooltip();
			}

			if (Button(ICON_FA_EXPAND)) [[unlikely]]
			{
				this->gizmo_op_ = ImGuizmo::OPERATION::SCALE;
			}

			if (IsItemHovered()) [[unlikely]]
			{
				BeginTooltip();
				TextUnformatted("Edit scale of selected object");
				EndTooltip();
			}

			if (Button(this->gizmo_mode_ == ImGuizmo::MODE::WORLD ? ICON_FA_GLOBE_STAND : ICON_FA_COMPASS)) [[unlikely]]
			{
				this->gizmo_mode_ = this->gizmo_mode_ == ImGuizmo::MODE::WORLD ? ImGuizmo::MODE::LOCAL : ImGuizmo::MODE::WORLD;
			}

			if (IsItemHovered()) [[unlikely]]
			{
				BeginTooltip();
				TextUnformatted(this->gizmo_mode_ == ImGuizmo::MODE::WORLD ? "Edit in world space" : "Edit in local space");
				EndTooltip();
			}

			Separator();

			if (Button(ICON_FA_CUBES)) [[unlikely]]
			{ }

			if (Button(ICON_FA_LIGHTBULB_ON)) [[unlikely]]
			{ }

			if (Button(ICON_FA_VOLUME_UP)) [[unlikely]]
			{ }

			if (Button(ICON_FA_TH)) [[unlikely]]
			{
				_rt.render_data().enable_wireframe = !_rt.render_data().enable_wireframe;
			}

			if (Button(ICON_FA_MAP_MARKER_SMILE)) [[unlikely]]
			{ }

			if (Button(ICON_FA_FUNCTION)) [[unlikely]]
			{ }

			if (Button(ICON_FA_SMILE)) [[unlikely]]
			{ }

			if (Button(ICON_FA_CAMERA)) [[unlikely]]
			{ }

			Separator();

			if (Button(_rt.is_playing() ? ICON_FA_STOP : ICON_FA_PLAY)) [[unlikely]]
			{
				const_cast<bool&>(_rt.is_playing()) = !_rt.is_playing();
			}
			if (Button(ICON_FA_PAUSE)) [[unlikely]]
			{ }
			PopStyleColor();
			EndMainMenuBar();
		}
	}

	void Editor::default_layout() const
	{
		if (this->dockspace_id_) [[likely]]
		{
			DockBuilderRemoveNode(this->dockspace_id_);
			DockBuilderAddNode(this->dockspace_id_, ImGuiDockNodeFlags_DockSpace);
			DockBuilderSetNodeSize(this->dockspace_id_, GetMainViewport()->Size);
			auto main_id = this->dockspace_id_;

			const auto dock_id_left = DockBuilderSplitNode(main_id, ImGuiDir_Left, .1f, nullptr, &main_id);
			const auto dock_id_right = DockBuilderSplitNode(main_id, ImGuiDir_Right, .25f, nullptr, &main_id);
			const auto dock_id_bottom = DockBuilderSplitNode(main_id, ImGuiDir_Down, .2f, nullptr, &main_id);

			DockBuilderDockWindow(HIERARCHY_NAME, dock_id_left);
			DockBuilderDockWindow(RESOURCE_VIEWER_NAME, dock_id_left);

			DockBuilderDockWindow(INSPECTOR_NAME, dock_id_right);
			DockBuilderDockWindow(CONFIG_EDITOR_NAME, dock_id_right);

			DockBuilderDockWindow(TERMINAL_NAME, dock_id_bottom);
			DockBuilderDockWindow(PROFILER_NAME, dock_id_bottom);

			DockBuilderDockWindow(SCENERY_VIEWER_NAME, main_id);

			DockBuilderFinish(this->dockspace_id_);
		}
	}

	void Editor::render_manipulator_gizmos(Transform* const _transform, RenderData& _data, const Config& _config) const noexcept
	{
		if (!_config.editor.show_gizmos) [[unlikely]]
		{
			return;
		}
		ImGuizmo::Enable(true);
		ImGuizmo::BeginFrame();
		const float x = _data.primary_viewport.x;
		const float y = _data.primary_viewport.y;
		const float w = _data.primary_viewport.z;
		const float h = _data.primary_viewport.w;
		ImGuizmo::SetRect(x, y, w, h);
		if (_config.editor.show_grid) [[likely]]
		{
			auto grid_pos_matrix = math::identity<SMat4x4<>>();
			grid_pos_matrix = math::translate(grid_pos_matrix, static_cast<SVec3<>>(_config.editor.grid_origin_center));
			ImGuizmo::DrawGrid(value_ptr(_data.view_matrix), value_ptr(_data.projection_matrix), value_ptr(grid_pos_matrix), _config.editor.grid_size);
		}

		if (!_transform) [[unlikely]]
		{
			return;
		}

		float tmp_matrix[16];
		auto eulers = math::eulerAngles(_transform->rotation);
		float mat_rotation[3] = {
			math::degrees(eulers.x),
			math::degrees(eulers.y),
			math::degrees(eulers.z),
		};
		ImGuizmo::RecomposeMatrixFromComponents(value_ptr(_transform->position), mat_rotation, value_ptr(_transform->scale), tmp_matrix);
		Manipulate(value_ptr(_data.view_matrix), value_ptr(_data.projection_matrix), this->gizmo_op_, this->gizmo_mode_, tmp_matrix);
		if (ImGuizmo::IsUsing()) [[unlikely]]
		{
			float mat_translation[3], mat_scale[3];
			ImGuizmo::DecomposeMatrixToComponents(tmp_matrix, mat_translation, mat_rotation, mat_scale);
			switch (this->gizmo_op_)
			{
				case ImGuizmo::OPERATION::TRANSLATE:
					_transform->position.x = mat_translation[0];
					_transform->position.y = mat_translation[1];
					_transform->position.z = mat_translation[2];
					break;

				case ImGuizmo::OPERATION::ROTATE:
					eulers = SVec3<>{math::radians(mat_rotation[0]), math::radians(mat_rotation[1]), math::radians(mat_rotation[2])};
					_transform->rotation = SQua<>(eulers);
					break;

				case ImGuizmo::OPERATION::SCALE:
					_transform->scale.x = mat_scale[0];
					_transform->scale.y = mat_scale[1];
					_transform->scale.z = mat_scale[2];
					break;

				default: break;
			}
		}
	}
}

#endif
