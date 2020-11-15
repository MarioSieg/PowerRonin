// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: shader_merger.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 12.11.2020 20:40

#include "shader_merger.hpp"
#include "../imgui_headers.hpp"
#include "../font_headers.hpp"
#include "../file_dialog_tool.hpp"
#include "../../../include/dce/proto.hpp"
#include "../../../include/dce/shader.hpp"

#include <filesystem>

using namespace ImGui;

namespace dce::gui::widgets {
	void ShaderMerger::initialize() {
		this->current_ = std::filesystem::current_path().string();
	}

	void ShaderMerger::update(bool &_show, AsyncProtocol &_proto) {
		[[likely]] if (Begin(ICON_FA_EYE " Shader Merger", &_show, ImGuiWindowFlags_AlwaysAutoResize)) {
			PushStyleColor(ImGuiCol_Button, 0x00000000);
			TextUnformatted("Vertex Shader");
			SameLine();
			[[unlikely]] if (SmallButton(ICON_FA_FOLDER_OPEN "##vs")) {
				char *path = nullptr;
				open_file_dialog(path, "bin, fxc", this->current_.c_str());
				[[likely]] if (path) {
					this->vs_file_ = path;
				}
				else {
					_proto.error("[Shader Merger] Invalid file selected!");
				}
			}
			SameLine();
			TextUnformatted(this->vs_file_.c_str());
			TextUnformatted("Fragment Shader");
			SameLine();
			[[unlikely]] if (SmallButton(ICON_FA_FOLDER_OPEN "##fs")) {
				char *path = nullptr;
				open_file_dialog(path, "bin, fxc", this->current_.c_str());
				[[likely]] if (path) {
					this->fs_file_ = path;
				}
				else {
					_proto.error("[Shader Merger] Invalid file selected!");
				}
			}
			SameLine();
			TextUnformatted(this->fs_file_.c_str());
			TextUnformatted("Output File");
			SameLine();
			[[unlikely]] if (SmallButton(ICON_FA_FOLDER_OPEN "##tt")) {
				char *path = nullptr;
				save_file_dialog(path, "cshader", this->current_.c_str());
				[[likely]] if (path) {
					this->target_ = path;
				}
				else {
					_proto.error("[Shader Merger] Invalid file selected!");
				}
			}
			SameLine();
			TextUnformatted(this->target_.c_str());
			PopStyleColor();
			[[unlikely]] if (Button(ICON_FA_COMPRESS_ARROWS_ALT " Merge")) {
				[[unlikely]] if (!std::filesystem::is_regular_file(this->vs_file_)) {
					_proto.error("[Shader Merger] Invalid vertex shader file: {}", this->vs_file_);
					return;
				}
				[[unlikely]] if (!std::filesystem::is_regular_file(this->fs_file_)) {
					_proto.error("[Shader Merger] Invalid fragment shader file: {}", this->fs_file_);
					return;
				}
				[[unlikely]] if (!Shader::combine_shader_files(this->vs_file_, this->fs_file_, this->target_)) {
					_proto.error("[Shader Merger] Failed to combine shader files!");
					return;
				}
				this->fs_file_.clear();
				this->vs_file_.clear();
				_proto.info("[Shader Merger] OK! Merged into: {}", this->target_);
				this->target_.clear();
			}
		}
		End();
	}
}
