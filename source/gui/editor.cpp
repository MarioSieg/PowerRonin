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
		SetNextWindowBgAlpha(.0F);
		this->dockspace_id_ = DockSpaceOverViewport(nullptr);

		[[unlikely]] if (this->first_use_) {
			this->default_layout();
			this->first_use_ = false;
		}

		[[likely]] if (this->show_menu_) {
			this->main_menu(_rt, _show_terminal);
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
			this->inspector_.update(this->show_inspector_, this->hierarchy_.get_selected(), _rt);
		}

		[[unlikely]] if (this->memory_editor_.Open) {
			this->memory_editor_.DrawWindow(MEMORY_EDITOR_NAME, &_rt, sizeof(Runtime));
		}

		[[unlikely]] if (this->show_config_editor_) {
			this->config_editor_.update(this->show_config_editor_, _rt.config(), _rt.scenery().config);
		}

		[[likely]] if (this->show_scenery_viewer_) {
			this->scenery_viewer_.update(this->show_scenery_viewer_, _rt.render_data());
		}

		const auto selected_entity = this->hierarchy_.get_selected();
		auto& registry = _rt.scenery().registry();

		[[likely]] if (registry.valid(selected_entity) && registry.has<Transform>(selected_entity)) {
			auto& transform = registry.get<Transform>(selected_entity);
			this->render_manipulator_gizmos(transform, _rt.render_data(), _rt.config());
		}
	}

	void Editor::main_menu(Runtime& _rt, bool& _show_terminal) {
		[[likely]] if (BeginMainMenuBar()) {
			[[unlikely]] if (BeginMenu("File")) {
				if (MenuItem("New")) {
				}
				if (MenuItem("Open")) {
				}
				if (MenuItem("Save")) {
				}
				if (MenuItem("Exit")) {
				}
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
				if (MenuItem(SCENERY_VIEWER_NAME)) {
					this->show_scenery_viewer_ = true;
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
			PushStyleColor(ImGuiCol_Button, 0x00000000);
			Separator();

			[[unlikely]] if (Button(ICON_FA_HAND_ROCK)) {
				this->gizmo_op_ = ImGuizmo::OPERATION::BOUNDS;
			}

			[[unlikely]] if (IsItemHovered()) {
				BeginTooltip();
				TextUnformatted("Edit bounds of selected object");
				EndTooltip();
			}

			[[unlikely]] if (Button(ICON_FA_ARROWS)) {
				this->gizmo_op_ = ImGuizmo::OPERATION::TRANSLATE;
			}

			[[unlikely]] if (IsItemHovered()) {
				BeginTooltip();
				TextUnformatted("Edit position of selected object");
				EndTooltip();
			}

			[[unlikely]] if (Button(ICON_FA_SYNC)) {
				this->gizmo_op_ = ImGuizmo::OPERATION::ROTATE;
			}

			[[unlikely]] if (IsItemHovered()) {
				BeginTooltip();
				TextUnformatted("Edit rotation of selected object");
				EndTooltip();
			}

			[[unlikely]] if (Button(ICON_FA_EXPAND)) {
				this->gizmo_op_ = ImGuizmo::OPERATION::SCALE;
			}

			[[unlikely]] if (IsItemHovered()) {
				BeginTooltip();
				TextUnformatted("Edit scale of selected object");
				EndTooltip();
			}

			[[unlikely]] if (Button(this->gizmo_mode_ == ImGuizmo::MODE::WORLD ? ICON_FA_GLOBE_STAND : ICON_FA_COMPASS)) {
				this->gizmo_mode_ = this->gizmo_mode_ == ImGuizmo::MODE::WORLD ? ImGuizmo::MODE::LOCAL : ImGuizmo::MODE::WORLD;
			}

			[[unlikely]] if (IsItemHovered()) {
				BeginTooltip();
				TextUnformatted(this->gizmo_mode_ == ImGuizmo::MODE::WORLD ? "Edit in world space" : "Edit in local space");
				EndTooltip();
			}

			Separator();

			[[unlikely]] if (Button(ICON_FA_CUBES)) {
			}

			[[unlikely]] if (Button(ICON_FA_LIGHTBULB_ON)) {
			}

			[[unlikely]] if (Button(ICON_FA_VOLUME_UP)) {
			}

			[[unlikely]] if (Button(ICON_FA_TH)) {
				_rt.render_data().enable_wireframe = !_rt.render_data().enable_wireframe;
			}

			[[unlikely]] if (Button(ICON_FA_MAP_MARKER_SMILE)) {
			}

			[[unlikely]] if (Button(ICON_FA_FUNCTION)) {
			}

			[[unlikely]] if (Button(ICON_FA_SMILE)) {
			}

			[[unlikely]] if (Button(ICON_FA_CAMERA)) {
			}

			Separator();

			[[unlikely]] if (Button(ICON_FA_PLAY)) {
			}
			[[unlikely]] if (Button(ICON_FA_PAUSE)) {
			}
			[[unlikely]] if (Button(ICON_FA_STOP)) {
			}
			PopStyleColor();
			EndMainMenuBar();
		}
	}

	void Editor::default_layout() const {
		[[likely]] if (this->dockspace_id_) {
			DockBuilderRemoveNode(this->dockspace_id_);
			DockBuilderAddNode(this->dockspace_id_, ImGuiDockNodeFlags_DockSpace);
			DockBuilderSetNodeSize(this->dockspace_id_, GetMainViewport()->Size);
			auto main_id = this->dockspace_id_;

			const auto dock_id_left = DockBuilderSplitNode(main_id, ImGuiDir_Left, .20f, nullptr, &main_id);
			const auto dock_id_right = DockBuilderSplitNode(main_id, ImGuiDir_Right, .20f, nullptr, &main_id);
			const auto dock_id_bottom = DockBuilderSplitNode(main_id, ImGuiDir_Down, .20f, nullptr, &main_id);

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

	void Editor::render_manipulator_gizmos(Transform& _transform, RenderData& _data, const Config& _config) const noexcept {
		[[unlikely]] if (!_config.editor.enable_gizmos) {
			return;
		}
		ImGuizmo::Enable(true);
		ImGuizmo::BeginFrame();
		const float x = _data.scenery_viewport_position.x;
		const float y = _data.scenery_viewport_position.y;
		const float w = _data.scenery_viewport_size.x;
		const float h = _data.scenery_viewport_size.y;
		ImGuizmo::SetRect(x, y, w, h);
		const auto grid_pos_matrix = math::identity<SimdMatrix4x4<>>();
		[[likely]] if (_config.editor.show_grid) {
			ImGuizmo::DrawGrid(value_ptr(_data.view_matrix), value_ptr(_data.projection_matrix), value_ptr(grid_pos_matrix),
			                   _config.editor.grid_size);
		}
		/*
		[[likely]] if (_config.editor.show_view_cube) {
			auto view = _data.view_matrix;
			ImGuizmo::ViewManipulate(value_ptr(view), 8.f, {x + w - 256.f, y}, {256.f, 256.f}, 0x10101010);
			const auto forward = normalize(SimdVector3<>(view[2]));
			view = math::inverse(view);
			const auto pos = SimdVector3<>(view[3][0], view[3][1], view[3][2]);
			_data.editor_camera.look_at_dir(forward);
			_data.editor_camera.position(pos);
		}
		*/
		float tmp_matrix[16];
		auto eulers = math::eulerAngles(_transform.rotation);
		float mat_rotation[3] = {
			math::degrees(eulers.x),
			math::degrees(eulers.y),
			math::degrees(eulers.z),
		};
		ImGuizmo::RecomposeMatrixFromComponents(value_ptr(_transform.position), mat_rotation, value_ptr(_transform.scale), tmp_matrix);
		Manipulate(value_ptr(_data.view_matrix), value_ptr(_data.projection_matrix), this->gizmo_op_, this->gizmo_mode_, tmp_matrix);
		static int i = 0;
		[[unlikely]] if (ImGuizmo::IsUsing()) {
			float mat_translation[3], mat_scale[3];
			ImGuizmo::DecomposeMatrixToComponents(tmp_matrix, mat_translation, mat_rotation, mat_scale);
			switch(this->gizmo_op_) {
				case ImGuizmo::OPERATION::TRANSLATE:
					_transform.position.x = mat_translation[0];
					_transform.position.y = mat_translation[1];
					_transform.position.z = mat_translation[2];
				break;

				case ImGuizmo::OPERATION::ROTATE:
					eulers = SimdVector3<>{ math::radians(mat_rotation[0]), math::radians(mat_rotation[1]), math::radians(mat_rotation[2]) };
					_transform.rotation = SimdQuaternion<>(eulers);
					++i;
					if (i > 100) {
						int noel = i;
					}
				break;

				case ImGuizmo::OPERATION::SCALE:
					_transform.scale.x = mat_scale[0];
					_transform.scale.y = mat_scale[1];
					_transform.scale.z = mat_scale[2];
				break;
			}
		}
	}
}
