#include "inspector.hpp"
#include "../gui_headers.hpp"
#include "../font_headers.hpp"
#include "../utils.hpp"
#include "../../include/dce/comcollections.hpp"
#include "../../include/dce/resource_manager.hpp"
#include "../file_dialog_tool.hpp"
#include "../window_names.hpp"

using namespace ImGui;

// Pls fix :'(
extern const float *VIEW, *PROJ;

namespace dce::gui::widgets {
	void Inspector::initialize() {
		this->current_path_ = std::filesystem::current_path().string();

		auto build_filter_extensions = [](auto& _string, const auto& _extensions) {
			for (const auto& ext : _extensions) {
				for (auto i = 1; i < ext.size(); ++i) {
					_string.push_back(ext[i]);
				}
				_string.push_back(',');
			}
		};

		build_filter_extensions(this->mesh_filer_, Mesh::FILE_EXTENSIONS);
		build_filter_extensions(this->texture_filer_, Texture::FILE_EXTENSIONS);
	}

	void Inspector::update(bool& _show, Registry& _registry, ResourceManager& _resource_manager, const ERef _entity) {
		SetNextWindowSize({300, 800}, ImGuiCond_FirstUseEver);
		[[likely]] if (Begin(INSPECTOR_NAME, &_show)) {
			[[unlikely]] if (!_registry.valid(_entity)) {
				TextUnformatted("No entity selected!");
				End();
				return;
			}
			const auto footer_height_to_reserve = GetStyle().ItemSpacing.y + GetFrameHeightWithSpacing();
			[[likely]] if (BeginChild("", {.0, -footer_height_to_reserve}, false)) {
				[[likely]] if (_registry.has<MetaData>(_entity)) {
					auto& meta = _registry.get<MetaData>(_entity);
					[[likely]] if (CollapsingHeader(ICON_FA_COGS " Metadata", ImGuiTreeNodeFlags_DefaultOpen)) {
						std::strncpy(this->string_buffer_.data(), meta.name.data(), BUFFER_SIZE);
						[[unlikely]] if (InputText("Name", this->string_buffer_.data(), BUFFER_SIZE)) {
							meta.name = this->string_buffer_.data();
						}

						std::strncpy(this->string_buffer_.data(), meta.description.data(), BUFFER_SIZE);
						[[unlikely]] if (InputText("Description", this->string_buffer_.data(), BUFFER_SIZE)) {
							meta.description = this->string_buffer_.data();
						}

						int tag = static_cast<int>(meta.tag);
						[[unlikely]] if (InputInt("Tag", &tag)) {
							meta.tag = static_cast<std::uint16_t>(tag);
						}

						int layer = static_cast<int>(meta.layer);
						[[unlikely]] if (InputInt("Layer", &layer)) {
							meta.layer = static_cast<std::uint16_t>(layer);
						}
					}
				}
				[[likely]] if (_registry.has<Transform>(_entity)) {
					auto& transform = _registry.get<Transform>(_entity);
					[[likely]] if (CollapsingHeader(
						ICON_FA_MAP_MARKER_ALT " Transform ", ImGuiTreeNodeFlags_DefaultOpen)) {
						[[unlikely]] if (Button(ICON_FA_ARROWS)) {
							this->modifier_ = ImGuizmo::TRANSLATE;
						}
						SameLine();
						[[unlikely]] if (Button(ICON_FA_SYNC)) {
							this->modifier_ = ImGuizmo::ROTATE;
						}
						SameLine();
						[[unlikely]] if (Button(ICON_FA_EXPAND)) {
							this->modifier_ = ImGuizmo::SCALE;
						}
						Separator();

						DragFloat3("Position", value_ptr(transform.position));

						Vector3<> euler_angles = eulerAngles(transform.rotation);
						euler_angles.x = math::degrees(euler_angles.x);
						euler_angles.y = math::degrees(euler_angles.y);
						euler_angles.z = math::degrees(euler_angles.z);
						[[unlikely]] if (DragFloat3("Rotation", value_ptr(euler_angles))) {
							euler_angles.x = math::radians(euler_angles.x);
							euler_angles.y = math::radians(euler_angles.y);
							euler_angles.z = math::radians(euler_angles.z);
							transform.rotation = Quaternion<>(euler_angles);
						}

						DragFloat3("Scale ", value_ptr(transform.scale));
						/*
						auto matrix = transform.calculate_matrix();
						ImGuizmo::Enable(true);
						ImGuizmo::BeginFrame();
						auto& io = GetIO();
						ImGuizmo::SetRect(.0f, .0f, io.DisplaySize.x, io.DisplaySize.y);
						[[unlikely]] if (Manipulate(VIEW, PROJ, this->modifier_, ImGuizmo::WORLD, value_ptr(matrix))) {
							glm::vec3 skew;
							glm::vec4 perspective;
							decompose(matrix, transform.scale, transform.rotation, transform.position, skew, perspective);
						}
						*/
					}
				}
				[[likely]] if (_registry.has<MeshRenderer>(_entity)) {
					auto& renderer = _registry.get<MeshRenderer>(_entity);
					[[likely]] if (CollapsingHeader(ICON_FA_CUBE " Mesh Renderer", ImGuiTreeNodeFlags_DefaultOpen)) {
						Checkbox("Visible", &renderer.is_visible);

						{
							const auto file_name = renderer.mesh->get_file_path().filename().string();
							PushStyleColor(ImGuiCol_Text, imgui_rgba(120, 212, 255));
							if (Button(file_name.c_str())) {
								char* path = nullptr;
								open_file_dialog(path, this->mesh_filer_.c_str(), this->current_path_.c_str());
								[[likely]] if (path) {
									renderer.mesh = _resource_manager.load<Mesh>(path);
								}
							}
							PopStyleColor();
							SameLine();
							TextUnformatted("Mesh");
						}
					}

					[[likely]] if (CollapsingHeader(ICON_FA_ADJUST " Material", ImGuiTreeNodeFlags_DefaultOpen)) {

						constexpr static const char* const material_names[] = {"Unlit", "Lambert"};
						/*
						[[unlikely]] if (BeginCombo("Shader", material_names[current])) {
							for (int i = 0; i < sizeof material_names / sizeof *material_names; ++i) {
								if (Selectable(material_names[i], current == i)) {
									current = i;
								}
								if (current == i) {
									SetItemDefaultFocus();
								}
							}
							EndCombo();
						}
						*/

						if (std::holds_alternative<Material::Unlit>(renderer.material->properties)) {
							auto& props = std::get<Material::Unlit>(renderer.material->properties);
							const auto file_name = props.albedo->get_file_path().filename().string();
							PushStyleColor(ImGuiCol_Text, imgui_rgba(120, 212, 255));
							if (Button(file_name.c_str())) {
								char* path = nullptr;
								open_file_dialog(path, this->texture_filer_.c_str(), this->current_path_.c_str());
								[[likely]] if (path) {
									props.albedo = _resource_manager.load<Texture>(path);
								}
							}
							PopStyleColor();
							SameLine();
							TextUnformatted("Albedo");
						}
						else if (std::holds_alternative<Material::Lambert>(renderer.material->properties)) {
							auto& props = std::get<Material::Lambert>(renderer.material->properties);
							const auto file_name = props.albedo->get_file_path().filename().string();
							PushStyleColor(ImGuiCol_Text, imgui_rgba(120, 212, 255));
							if (Button(file_name.c_str())) {
								char* path = nullptr;
								open_file_dialog(path, this->texture_filer_.c_str(), this->current_path_.c_str());
								[[likely]] if (path) {
									props.albedo = _resource_manager.load<Texture>(path);
								}
							}
							PopStyleColor();
						}
					}
				}

				[[unlikely]] if (_registry.has<Rigidbody>(_entity)) {
					auto& rigidbody = _registry.get<Rigidbody>(_entity);
					[[likely]] if (CollapsingHeader(ICON_FA_GLOBE " Rigidbody", ImGuiTreeNodeFlags_DefaultOpen)) {
						DragFloat("Mass", &rigidbody.mass);
						Checkbox("Is Kinematic", &rigidbody.is_kinematic);
					}
				}
				EndChild();
			}
		}
		End();
	}
}
