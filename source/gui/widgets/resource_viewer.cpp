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

#include "resource_viewer.hpp"
#include "../font_headers.hpp"
#include "../gui_headers.hpp"
#include "../utils.hpp"
#include "../../../include/dce/resource_manager.hpp"
#include "../window_names.hpp"

using namespace ImGui;

namespace dce::gui::widgets {
	void ResourceViewer::update(bool& _show, ResourceManager& _rm) {
		SetNextWindowSize({800, 600}, ImGuiCond_FirstUseEver);
		[[likely]] if (Begin(RESOURCE_VIEWER_NAME, &_show)) {
			Text("Textures: %u", static_cast<unsigned>(_rm.get_texture_cache().size()));
			SameLine();
			Text("Meshes: %u", static_cast<unsigned>(_rm.get_mesh_cache().size()));
			Separator();
			Spacing();
			if (CollapsingHeader(ICON_FA_IMAGES " Textures")) {
				_rm.get_texture_cache().each([&](const RRef<Texture>& _texture) {
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
				_rm.get_mesh_cache().each([](const RRef<Mesh>& _mesh) {
					TextUnformatted(ICON_FA_CUBE);
					SameLine();
					TextUnformatted(_mesh->get_file_path().filename().string().c_str());
					if (IsItemHovered()) {
						const auto size = _mesh->get_vertices().size() * sizeof(Vertex) + _mesh->get_indices().size() * sizeof(std::uint16_t);
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
			/*
			[[likely]] if (CollapsingHeader(ICON_FA_EYE " Shaders")) {
			        _rm.shader_cache.each([](const RRef<Shader> &_shader) {
			                TextUnformatted(ICON_FA_EYE);
			                SameLine();
			                TextUnformatted(_shader->get_file_path().filename().string().c_str());
			                if (IsItemHovered()) {
			                        BeginTooltip();
			                        TextUnformatted(_shader->is_uploaded() ? "Uploaded: yes" : "Uploaded: no");
			                        const auto vs_size = _shader->get_vertex_shader_bytecode().size() * sizeof(std::byte);
			                        Text("Vertex Shader Size: %zuB", vs_size);
			                        std::size_t fs_size = 0;
			                        [[likely]] if (_shader->get_fragment_shader_bytecode()) {
			                                fs_size = (*_shader->get_fragment_shader_bytecode()).size() * sizeof(std::byte);
			                                Text("Fragment Shader Size: %zuB", fs_size);
			                        }
			                        Text("Total Size: %zuB", vs_size + fs_size);
			                        Text("Uniforms: %zu", _shader->get_uniforms().size());
			                        Separator();
			                        for (const auto &uniform : _shader->get_uniforms()) {
			                                TextUnformatted(uniform.first.data());
			                                SameLine();
			                                const char *type = "";
			                                switch (std::get<0>(uniform.second)) {
			                                default: case UniformType::SAMPLER: type = ": Sampler";
			                                        break;
			                                case UniformType::MATRIX_3x3: type = ": Matrix3x3";
			                                        break;
			                                case UniformType::MATRIX_4x4: type = ": Matrix4x4";
			                                        break;
			                                case UniformType::VEC_4: type = ": Vector4";
			                                        break;
			                                }
			                                TextUnformatted(type);
			                        }
			                        EndTooltip();
			                }
			                Separator();
			        });
			}
			*/
		}
		End();
	}
} // namespace dce::gui::widgets // namespace dce::gui::widgets
