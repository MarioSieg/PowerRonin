// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: resource_viewer.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 06.11.2020 22:18

#include "resource_viewer.hpp"
#include "../font_headers.hpp"
#include "../imgui_headers.hpp"
#include "../utils.hpp"
#include "../../../include/dce/resource_manager.hpp"

using namespace ImGui;

namespace dce::gui::widgets {
	void ResourceViewer::update(bool &_show, ResourceManager &_importeur) {
		SetNextWindowSize({800, 600}, ImGuiCond_FirstUseEver);
		[[likely]] if (Begin(ICON_FA_DATABASE " Resource Viewer", &_show)) {
			Text("Textures: %u", static_cast<unsigned>(_importeur.texture_cache.size()));
			SameLine();
			Text("Meshes: %u", static_cast<unsigned>(_importeur.mesh_cache.size()));
			Separator();
			Spacing();
			if (CollapsingHeader(ICON_FA_IMAGES " Textures")) {
				_importeur.texture_cache.each([&](const ResourceHandle<Texture> &_texture) {
					TextUnformatted(ICON_FA_IMAGE);
					SameLine();
					TextUnformatted(_texture->get_file_path().filename().string().c_str());
					if (IsItemHovered()) {
						BeginTooltip();
						if (_texture->is_uploaded()) {
							image(_texture, {128.f, 128.f}, {.0f, .0f}, {1.0f, 1.0f});
						}
						TextUnformatted(_texture->is_uploaded() ? "Uploaded: yes" : "Uploaded: no");
						Text("Width: %u", _texture->get_width());
						Text("Height: %u", _texture->get_height());
						Text("Size: %zuB", _texture->get_storage_size());
						Text("Format: %s", get_format_name(_texture->get_format()).data());
						Text("Mipmaps: %u", _texture->get_mipmap_count());
						Text("BPS: %u", _texture->get_bits_per_pixel());
						EndTooltip();
					}
					Separator();
				});
			}
			[[likely]] if (CollapsingHeader(ICON_FA_CUBES " Meshes")) {
				_importeur.mesh_cache.each([](const ResourceHandle<Mesh> &_mesh) {
					TextUnformatted(ICON_FA_CUBE);
					SameLine();
					TextUnformatted(_mesh->get_file_path().filename().string().c_str());
					if (IsItemHovered()) {
						const auto size = _mesh->get_vertices().size() * sizeof(Vertex) + _mesh->get_indices().size() * sizeof
							std::uint16_t;
						BeginTooltip();
						TextUnformatted(_mesh->is_uploaded() ? "Uploaded: yes" : "Uploaded: no");
						Text("Vertices: %zu", _mesh->get_vertices().size());
						Text("Indices: %zu", _mesh->get_indices().size());
						Text("Size: %zuB", size);
						EndTooltip();
					}
					Separator();
				});
			}
			[[likely]] if (CollapsingHeader(ICON_FA_EYE " Shaders")) {
				_importeur.shader_cache.each([](const ResourceHandle<Shader> &_shader) {
					TextUnformatted(ICON_FA_EYE);
					SameLine();
					TextUnformatted(_shader->get_file_path().filename().string().c_str());
					if (IsItemHovered()) {
						BeginTooltip();
						TextUnformatted(_shader->is_uploaded() ? "Uploaded: yes" : "Uploaded: no");
						const auto vs_size = _shader->get_vertex_shader_bytecode().size() * sizeof(std::byte);
						const auto fs_size = _shader->get_fragment_shader_bytecode().size() * sizeof(std::byte);
						Text("Vertex Shader Size: %zuB", vs_size);
						Text("Fragment Shader Size: %zuB", fs_size);
						Text("Total Size: %zuB", vs_size + fs_size);
						EndTooltip();
					}
					Separator();
				});
			}
		}
		End();
	}
} // namespace dce::gui::widgets // namespace dce::gui::widgets
