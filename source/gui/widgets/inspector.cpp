#if AUTO_TEC

#include "inspector.hpp"
#include "../gui_headers.hpp"
#include "../font_headers.hpp"
#include "../utils.hpp"
#include "../../Include/PowerRonin/Components.hpp"
#include "../../Include/PowerRonin/ResourceManager.hpp"
#include "../file_dialog_tool.hpp"
#include "../window_names.hpp"
#include "../../../Include/PowerRonin/RenderState.hpp"
#include "../../../Include/PowerRonin/Runtime.hpp"

using namespace ImGui;

namespace PowerRonin::Interface::widgets
{
	void Inspector::initialize()
	{
		this->current_path_ = std::filesystem::current_path().string();

		auto build_filter_extensions = [](auto& _string, const auto& _extensions)
		{
			for (const auto& ext : _extensions)
			{
				for (auto i = 1; i < ext.size(); ++i)
				{
					_string.push_back(ext[i]);
				}
				_string.push_back(',');
			}
		};

		build_filter_extensions(this->mesh_filer_, Mesh::FileExtensions);
		build_filter_extensions(this->texture_filer_, Texture::FILE_EXTENSIONS);
	}

	void Inspector::update(bool& _show, const EntityRef _entity, Runtime& _rt)
	{
		auto& registry = _rt.Scenery().registry();
		SetNextWindowSize({300, 800}, ImGuiCond_FirstUseEver);
		if (Begin(INSPECTOR_NAME, &_show)) [[likely]]
		{
			if (!registry.valid(_entity)) [[unlikely]]
			{
				TextUnformatted("Select an entity in the hierarchy");
				End();
				return;
			}
			const auto footer_height_to_reserve = GetStyle().ItemSpacing.y + GetFrameHeightWithSpacing();
			if (BeginChild("", {.0, -footer_height_to_reserve}, false)) [[likely]]
			{
				if (registry.has<MetaData>(_entity)) [[likely]]
				{
					auto& meta = registry.get<MetaData>(_entity);
					if (CollapsingHeader(ICON_FA_COGS " Metadata", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
					{
						std::strncpy(this->string_buffer_.data(), meta.Name.data(), BUFFER_SIZE);
						if (InputText("Name", this->string_buffer_.data(), BUFFER_SIZE)) [[unlikely]]
						{
							meta.Name = this->string_buffer_.data();
						}

						std::strncpy(this->string_buffer_.data(), meta.Description.data(), BUFFER_SIZE);
						if (InputText("Description", this->string_buffer_.data(), BUFFER_SIZE)) [[unlikely]]
						{
							meta.Description = this->string_buffer_.data();
						}

						int tag = static_cast<int>(meta.Tag);
						if (InputInt("Tag", &tag)) [[unlikely]]
						{
							meta.Tag = static_cast<std::uint16_t>(tag);
						}

						int layer = static_cast<int>(meta.Layer);
						if (InputInt("Layer", &layer)) [[unlikely]]
						{
							meta.Layer = static_cast<std::uint16_t>(layer);
						}
					}
				}
				if (registry.has<Transform>(_entity)) [[likely]]
				{
					auto& transform = registry.get<Transform>(_entity);
					if (CollapsingHeader(ICON_FA_MAP_MARKER_ALT " Transform ", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
					{

						DragFloat3("Position", value_ptr(transform.position));

						Vector3<> euler_angles = eulerAngles(transform.rotation);
						euler_angles.x = Math::degrees(euler_angles.x);
						euler_angles.y = Math::degrees(euler_angles.y);
						euler_angles.z = Math::degrees(euler_angles.z);
						if (DragFloat3("Rotation", value_ptr(euler_angles))) [[unlikely]]
						{
							euler_angles.x = Math::radians(euler_angles.x);
							euler_angles.y = Math::radians(euler_angles.y);
							euler_angles.z = Math::radians(euler_angles.z);
							transform.rotation = Quaternion<>(euler_angles);
						}

						DragFloat3("Scale ", value_ptr(transform.scale));
					}
				}
				if (registry.has<MeshRenderer>(_entity)) [[likely]]
				{
					auto& renderer = registry.get<MeshRenderer>(_entity);
					if (CollapsingHeader(ICON_FA_CUBE " Mesh Renderer", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
					{
						Checkbox("Visible", &renderer.IsVisible);

						{
							const auto file_name = renderer.Mesh->FilePath().filename().string();
							PushStyleColor(ImGuiCol_Text, imgui_rgba(120, 212, 255));
							if (Button(file_name.c_str()))
							{
								char* path = nullptr;
								open_file_dialog(path, this->mesh_filer_.c_str(), this->current_path_.c_str());
								if (path) [[likely]]
								{
									renderer.Mesh = _rt.ResourceManager().Load<Mesh>(path);
								}
							}
							PopStyleColor();
							SameLine();
							TextUnformatted("Mesh");
						}
					}

					if (CollapsingHeader(ICON_FA_ADJUST " Material", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
					{

						if (std::holds_alternative<Material::UnlitTextured>(renderer.Material->Properties))
						{
							auto& props = std::get<Material::UnlitTextured>(renderer.Material->Properties);
							const auto file_name = props.Albedo->FilePath().filename().string();
							PushStyleColor(ImGuiCol_Text, imgui_rgba(120, 212, 255));
							if (Button(file_name.c_str())) [[unlikely]]
							{
								char* path = nullptr;
								open_file_dialog(path, this->texture_filer_.c_str(), this->current_path_.c_str());
								if (path) [[likely]]
								{
									props.Albedo = _rt.ResourceManager().Load<Texture>(path);
								}
							}
							PopStyleColor();
							DragFloat2("Tiling", &props.TilingOffset.x);
							DragFloat2("Offset", &props.TilingOffset.z, .01F, .0F, 1.F);
						}
						else if (std::holds_alternative<Material::Diffuse>(renderer.Material->Properties)) [[likely]]
						{
							auto& props = std::get<Material::Diffuse>(renderer.Material->Properties);
							const auto file_name = props.Albedo->FilePath().filename().string();
							PushStyleColor(ImGuiCol_Text, imgui_rgba(120, 212, 255));
							if (Button(file_name.c_str())) [[unlikely]]
							{
								char* path = nullptr;
								open_file_dialog(path, this->texture_filer_.c_str(), this->current_path_.c_str());
								if (path) [[likely]]
								{
									props.Albedo = _rt.ResourceManager().Load<Texture>(path);
								}
							}
							PopStyleColor();
							DragFloat2("Tiling", &props.TilingOffset.x);
							DragFloat2("Offset", &props.TilingOffset.z, .01F, .0F, 1.F);
						}
						else if (std::holds_alternative<Material::BumpedDiffuse>(renderer.Material->Properties)) [[likely]]
						{
							auto& props = std::get<Material::BumpedDiffuse>(renderer.Material->Properties);
							const auto albedo_file = props.Albedo->FilePath().filename().string();
							const auto normal_file = props.Normal->FilePath().filename().string();
							PushStyleColor(ImGuiCol_Text, imgui_rgba(120, 212, 255));
							if (Button(albedo_file.c_str())) [[unlikely]]
							{
								char* path = nullptr;
								open_file_dialog(path, this->texture_filer_.c_str(), this->current_path_.c_str());
								if (path) [[likely]]
								{
									props.Albedo = _rt.ResourceManager().Load<Texture>(path);
								}
							}
							if (Button(normal_file.c_str())) [[unlikely]]
							{
								char* path = nullptr;
								open_file_dialog(path, this->texture_filer_.c_str(), this->current_path_.c_str());
								if (path) [[likely]]
								{
									props.Normal = _rt.ResourceManager().Load<Texture>(path);
								}
							}
							PopStyleColor();
							DragFloat2("Tiling", &props.TilingOffset.x);
							DragFloat2("Offset", &props.TilingOffset.z, .01F, .0F, 1.F);
						}
					}
				}

				if (registry.has<Camera>(_entity)) [[unlikely]]
				{
					auto& camera = registry.get<Camera>(_entity);
					if (CollapsingHeader(ICON_FA_CAMERA " Camera", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
					{
						SliderFloat("FOV Y", &camera.Fov, 2.F, 150.F);
						InputFloat2("Near Far Z Clip", &camera.NearClip);
					}
				}

				if (registry.has<Rigidbody>(_entity)) [[unlikely]]
				{
					auto& rigidbody = registry.get<Rigidbody>(_entity);
					if (CollapsingHeader(ICON_FA_GLOBE " Rigidbody", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
					{
						DragFloat("Mass", &rigidbody.Mass);
						Checkbox("Is Kinematic", &rigidbody.IsKinematic);
					}
				}
				EndChild();
			}
		}
		End();
	}
}

#endif
