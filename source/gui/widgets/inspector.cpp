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

#include "inspector.hpp"
#include "../gui_headers.hpp"
#include "../font_headers.hpp"
#include "../utils.hpp"
#include "../../include/power_ronin/comcollections.hpp"
#include "../../include/power_ronin/resource_manager.hpp"
#include "../file_dialog_tool.hpp"
#include "../window_names.hpp"
#include "../../../include/power_ronin/renderer_data.hpp"
#include "../../../include/power_ronin/runtime.hpp"

using namespace ImGui;

// Pls fix :'(
extern const float *VIEW, *PROJ;

namespace power_ronin::gui::widgets
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

		build_filter_extensions(this->mesh_filer_, Mesh::FILE_EXTENSIONS);
		build_filter_extensions(this->texture_filer_, Texture::FILE_EXTENSIONS);
	}

	void Inspector::update(bool& _show, const ERef _entity, Runtime& _rt)
	{
		auto& registry = _rt.scenery().registry();
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
						std::strncpy(this->string_buffer_.data(), meta.name.data(), BUFFER_SIZE);
						if (InputText("Name", this->string_buffer_.data(), BUFFER_SIZE)) [[unlikely]]
						{
							meta.name = this->string_buffer_.data();
						}

						std::strncpy(this->string_buffer_.data(), meta.description.data(), BUFFER_SIZE);
						if (InputText("Description", this->string_buffer_.data(), BUFFER_SIZE)) [[unlikely]]
						{
							meta.description = this->string_buffer_.data();
						}

						int tag = static_cast<int>(meta.tag);
						if (InputInt("Tag", &tag)) [[unlikely]]
						{
							meta.tag = static_cast<std::uint16_t>(tag);
						}

						int layer = static_cast<int>(meta.layer);
						if (InputInt("Layer", &layer)) [[unlikely]]
						{
							meta.layer = static_cast<std::uint16_t>(layer);
						}
					}
				}
				if (registry.has<Transform>(_entity)) [[likely]]
				{
					auto& transform = registry.get<Transform>(_entity);
					if (CollapsingHeader(ICON_FA_MAP_MARKER_ALT " Transform ", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
					{

						DragFloat3("Position", value_ptr(transform.position));

						SVec3<> euler_angles = eulerAngles(transform.rotation);
						euler_angles.x = math::degrees(euler_angles.x);
						euler_angles.y = math::degrees(euler_angles.y);
						euler_angles.z = math::degrees(euler_angles.z);
						if (DragFloat3("Rotation", value_ptr(euler_angles))) [[unlikely]]
						{
							euler_angles.x = math::radians(euler_angles.x);
							euler_angles.y = math::radians(euler_angles.y);
							euler_angles.z = math::radians(euler_angles.z);
							transform.rotation = SQua<>(euler_angles);
						}

						DragFloat3("Scale ", value_ptr(transform.scale));
					}
				}
				if (registry.has<MeshRenderer>(_entity)) [[likely]]
				{
					auto& renderer = registry.get<MeshRenderer>(_entity);
					if (CollapsingHeader(ICON_FA_CUBE " Mesh Renderer", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
					{
						Checkbox("Visible", &renderer.is_visible);

						{
							const auto file_name = renderer.mesh->file_path().filename().string();
							PushStyleColor(ImGuiCol_Text, imgui_rgba(120, 212, 255));
							if (Button(file_name.c_str()))
							{
								char* path = nullptr;
								open_file_dialog(path, this->mesh_filer_.c_str(), this->current_path_.c_str());
								if (path) [[likely]]
								{
									renderer.mesh = _rt.resource_manager().load<Mesh>(path);
								}
							}
							PopStyleColor();
							SameLine();
							TextUnformatted("Mesh");
						}
					}

					if (CollapsingHeader(ICON_FA_ADJUST " Material", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
					{

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

						if (std::holds_alternative<Material::UnlitTextured>(renderer.material->properties))
						{
							auto& props = std::get<Material::UnlitTextured>(renderer.material->properties);
							const auto file_name = props.albedo->file_path().filename().string();
							PushStyleColor(ImGuiCol_Text, imgui_rgba(120, 212, 255));
							if (Button(file_name.c_str())) [[unlikely]]
							{
								char* path = nullptr;
								open_file_dialog(path, this->texture_filer_.c_str(), this->current_path_.c_str());
								if (path) [[likely]]
								{
									props.albedo = _rt.resource_manager().load<Texture>(path);
								}
							}
							PopStyleColor();
							DragFloat2("Tiling", &props.tiling_offset.x);
							DragFloat2("Offset", &props.tiling_offset.z, .01F, .0F, 1.F);
						}
						else if (std::holds_alternative<Material::Diffuse>(renderer.material->properties)) [[likely]]
						{
							auto& props = std::get<Material::Diffuse>(renderer.material->properties);
							const auto file_name = props.albedo->file_path().filename().string();
							PushStyleColor(ImGuiCol_Text, imgui_rgba(120, 212, 255));
							if (Button(file_name.c_str())) [[unlikely]]
							{
								char* path = nullptr;
								open_file_dialog(path, this->texture_filer_.c_str(), this->current_path_.c_str());
								if (path) [[likely]]
								{
									props.albedo = _rt.resource_manager().load<Texture>(path);
								}
							}
							PopStyleColor();
							DragFloat2("Tiling", &props.tiling_offset.x);
							DragFloat2("Offset", &props.tiling_offset.z, .01F, .0F, 1.F);
						}
						else if (std::holds_alternative<Material::BumpedDiffuse>(renderer.material->properties)) [[likely]]
						{
							auto& props = std::get<Material::BumpedDiffuse>(renderer.material->properties);
							const auto albedo_file = props.albedo->file_path().filename().string();
							const auto normal_file = props.normal->file_path().filename().string();
							PushStyleColor(ImGuiCol_Text, imgui_rgba(120, 212, 255));
							if (Button(albedo_file.c_str())) [[unlikely]]
							{
								char* path = nullptr;
								open_file_dialog(path, this->texture_filer_.c_str(), this->current_path_.c_str());
								if (path) [[likely]]
								{
									props.albedo = _rt.resource_manager().load<Texture>(path);
								}
							}
							if (Button(normal_file.c_str())) [[unlikely]]
							{
								char* path = nullptr;
								open_file_dialog(path, this->texture_filer_.c_str(), this->current_path_.c_str());
								if (path) [[likely]]
								{
									props.normal = _rt.resource_manager().load<Texture>(path);
								}
							}
							PopStyleColor();
							DragFloat2("Tiling", &props.tiling_offset.x);
							DragFloat2("Offset", &props.tiling_offset.z, .01F, .0F, 1.F);
						}
					}
				}

				if (registry.has<Rigidbody>(_entity)) [[unlikely]]
				{
					auto& rigidbody = registry.get<Rigidbody>(_entity);
					if (CollapsingHeader(ICON_FA_GLOBE " Rigidbody", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
					{
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

#endif
