// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: dockspace.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "dockspace.hpp"
#include "gui_headers.hpp"

namespace dce::gui {
	void begin_dockspace() {
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
		ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		if constexpr (IS_FULLSCREEN_DOCKSPACE) {
			auto *const viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);

			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, .0F);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, .0F);

			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else {
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if constexpr (!IS_PADDING_DOCKSPACE) {
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0F, 0.0F));
		}

		ImGui::Begin("DockSpace", nullptr, window_flags);

		if constexpr (!IS_PADDING_DOCKSPACE) {
			ImGui::PopStyleVar();
		}

		if constexpr (IS_FULLSCREEN_DOCKSPACE) {
			ImGui::PopStyleVar(2);
		}

		// DockSpace:
		auto &io = ImGui::GetIO();
		[[likely]] if ((io.ConfigFlags & ImGuiConfigFlags_DockingEnable) != 0) {
			const auto dockspaceID = ImGui::GetID("DockSpace");
			ImGui::DockSpace(dockspaceID, ImVec2(0.0F, 0.0F), dockspace_flags);
		}
		else {
			ImGui::Text("Docking is not enabled!");
			ImGui::SameLine(.0F, .0F);
			if (ImGui::SmallButton("Enable")) {
				io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			}
		}
	}

	void end_dockspace() {
		ImGui::End();
	}
} // namespace dce::gui // namespace dce::gui
