// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: theme.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "theme.hpp"
#include "gui_headers.hpp"

namespace dce::gui {
	void style_dark() noexcept {
		auto& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Text] = ImVec4(1.00F, 1.00F, 1.00F, 1.00F);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50F, 0.50F, 0.50F, 1.00F);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06F, 0.06F, 0.06F, 0.94F);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(1.00F, 1.00F, 1.00F, 0.00F);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08F, 0.08F, 0.08F, 0.94F);
		style.Colors[ImGuiCol_Border] = ImVec4(0.43F, 0.43F, 0.50F, 0.50F);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00F, 0.00F, 0.00F, 0.00F);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20F, 0.21F, 0.22F, 0.54F);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.40F, 0.40F, 0.40F, 0.40F);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.18F, 0.18F, 0.18F, 0.67F);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.04F, 0.04F, 0.04F, 1.00F);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.29F, 0.29F, 0.29F, 1.00F);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00F, 0.00F, 0.00F, 0.51F);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14F, 0.14F, 0.14F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02F, 0.02F, 0.02F, 0.53F);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31F, 0.31F, 0.31F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41F, 0.41F, 0.41F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51F, 0.51F, 0.51F, 1.00F);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.94F, 0.94F, 0.94F, 1.00F);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.51F, 0.51F, 0.51F, 1.00F);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.86F, 0.86F, 0.86F, 1.00F);
		style.Colors[ImGuiCol_Button] = ImVec4(0.44F, 0.44F, 0.44F, 0.40F);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.46F, 0.47F, 0.48F, 1.00F);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.42F, 0.42F, 0.42F, 1.00F);
		style.Colors[ImGuiCol_Header] = ImVec4(0.70F, 0.70F, 0.70F, 0.31F);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.70F, 0.70F, 0.70F, 0.80F);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.48F, 0.50F, 0.52F, 1.00F);
		style.Colors[ImGuiCol_Separator] = ImVec4(0.43F, 0.43F, 0.50F, 0.50F);
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.72F, 0.72F, 0.72F, 0.78F);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.51F, 0.51F, 0.51F, 1.00F);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.91F, 0.91F, 0.91F, 0.25F);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.81F, 0.81F, 0.81F, 0.67F);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.46F, 0.46F, 0.46F, 0.95F);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61F, 0.61F, 0.61F, 1.00F);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00F, 0.43F, 0.35F, 1.00F);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.73F, 0.60F, 0.15F, 1.00F);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00F, 0.60F, 0.00F, 1.00F);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.87F, 0.87F, 0.87F, 0.35F);
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80F, 0.80F, 0.80F, 0.35F);
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00F, 1.00F, 0.00F, 0.90F);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.60F, 0.60F, 0.60F, 1.00F);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00F, 1.00F, 1.00F, 0.70F);
		style.Colors[ImGuiCol_Tab] = ImVec4(0.04F, 0.04F, 0.04F, 1.00F);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.29F, 0.29F, 0.29F, 1.00F);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.20F, 0.21F, 0.22F, 0.54F);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.00F, 0.00F, 0.00F, 0.51F);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.00F, 0.00F, 0.00F, 0.51F);
	}

	void style_light() noexcept {
		auto& style = ImGui::GetStyle();
		style.FrameRounding = 3.0F;
		style.Colors[ImGuiCol_Text] = ImVec4(0.00F, 0.00F, 0.00F, 1.00F);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60F, 0.60F, 0.60F, 1.00F);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94F, 0.94F, 0.94F, 0.94F);
		//style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00F, 1.00F, 1.00F, 0.94F);
		style.Colors[ImGuiCol_Border] = ImVec4(0.00F, 0.00F, 0.00F, 0.39F);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00F, 1.00F, 1.00F, 0.10F);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00F, 1.00F, 1.00F, 0.94F);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26F, 0.59F, 0.98F, 0.40F);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26F, 0.59F, 0.98F, 0.67F);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96F, 0.96F, 0.96F, 1.00F);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00F, 1.00F, 1.00F, 0.51F);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82F, 0.82F, 0.82F, 1.00F);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86F, 0.86F, 0.86F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98F, 0.98F, 0.98F, 0.53F);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69F, 0.69F, 0.69F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59F, 0.59F, 0.59F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49F, 0.49F, 0.49F, 1.00F);
		//style.Colors[ImGuiCol_ComboBg] = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26F, 0.59F, 0.98F, 1.00F);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24F, 0.52F, 0.88F, 1.00F);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26F, 0.59F, 0.98F, 1.00F);
		style.Colors[ImGuiCol_Button] = ImVec4(0.26F, 0.59F, 0.98F, 0.40F);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26F, 0.59F, 0.98F, 1.00F);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06F, 0.53F, 0.98F, 1.00F);
		style.Colors[ImGuiCol_Header] = ImVec4(0.26F, 0.59F, 0.98F, 0.31F);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26F, 0.59F, 0.98F, 0.80F);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26F, 0.59F, 0.98F, 1.00F);
		//style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		//style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
		//style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		//style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26F, 0.59F, 0.98F, 0.67F);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26F, 0.59F, 0.98F, 0.95F);
		//style.Colors[ImGuiCol_CloseButton] = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
		//style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
		//style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39F, 0.39F, 0.39F, 1.00F);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00F, 0.43F, 0.35F, 1.00F);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90F, 0.70F, 0.00F, 1.00F);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00F, 0.60F, 0.00F, 1.00F);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26F, 0.59F, 0.98F, 0.35F);
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20F, 0.20F, 0.20F, 0.35F);
	}

	void style_cherry() noexcept {
		auto& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Text] = ImVec4(0.860F, 0.930F, 0.890F, 0.78F);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.860F, 0.930F, 0.890F, 0.28F);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13F, 0.14F, 0.17F, 1.00F);
		//style.Colors[ImGuiCol_ChildWindowBg] = BG(0.58f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.200F, 0.220F, 0.270F, 0.9F);
		style.Colors[ImGuiCol_Border] = ImVec4(0.31F, 0.31F, 1.00F, 0.00F);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00F, 0.00F, 0.00F, 0.00F);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.200F, 0.220F, 0.270F, 1.00F);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.455F, 0.198F, 0.301F, 0.78F);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.455F, 0.198F, 0.301F, 1.00F);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.232F, 0.201F, 0.271F, 1.00F);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.502F, 0.075F, 0.256F, 1.00F);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.200F, 0.220F, 0.270F, 0.75F);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.200F, 0.220F, 0.270F, 0.47F);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.200F, 0.220F, 0.270F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09F, 0.15F, 0.16F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.455F, 0.198F, 0.301F, 0.78F);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.455F, 0.198F, 0.301F, 1.00F);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71F, 0.22F, 0.27F, 1.00F);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47F, 0.77F, 0.83F, 0.14F);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.71F, 0.22F, 0.27F, 1.00F);
		style.Colors[ImGuiCol_Button] = ImVec4(0.47F, 0.77F, 0.83F, 0.14F);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.455F, 0.198F, 0.301F, 0.86F);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.455F, 0.198F, 0.301F, 1.00F);
		style.Colors[ImGuiCol_Header] = ImVec4(0.455F, 0.198F, 0.301F, 0.76F);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.455F, 0.198F, 0.301F, 0.86F);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.502F, 0.075F, 0.256F, 1.00F);
		//style.Colors[ImGuiCol_Column] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
		//style.Colors[ImGuiCol_ColumnHovered] = MED(0.78f);
		//style.Colors[ImGuiCol_ColumnActive] = MED(1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47F, 0.77F, 0.83F, 0.04F);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.455F, 0.198F, 0.301F, 0.78F);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.455F, 0.198F, 0.301F, 1.00F);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.860F, 0.930F, 0.890F, 0.63F);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.455F, 0.198F, 0.301F, 1.00F);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.860F, 0.930F, 0.890F, 0.63F);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.455F, 0.198F, 0.301F, 1.00F);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.455F, 0.198F, 0.301F, 0.43F);
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.200F, 0.220F, 0.270F, 0.73F);
		style.Colors[ImGuiCol_Border] = ImVec4(0.539F, 0.479F, 0.255F, 0.162F);
	}

	void style_blue() noexcept {
		auto& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Text] = ImVec4(0.95F, 0.96F, 0.98F, 1.00F);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.36F, 0.42F, 0.47F, 1.00F);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.11F, 0.15F, 0.17F, 1.00F);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.15F, 0.18F, 0.22F, 1.00F);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08F, 0.08F, 0.08F, 0.94F);
		style.Colors[ImGuiCol_Border] = ImVec4(0.08F, 0.10F, 0.12F, 1.00F);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00F, 0.00F, 0.00F, 0.00F);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20F, 0.25F, 0.29F, 1.00F);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12F, 0.20F, 0.28F, 1.00F);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.09F, 0.12F, 0.14F, 1.00F);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.09F, 0.12F, 0.14F, 0.65F);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08F, 0.10F, 0.12F, 1.00F);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00F, 0.00F, 0.00F, 0.51F);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.15F, 0.18F, 0.22F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02F, 0.02F, 0.02F, 0.39F);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20F, 0.25F, 0.29F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18F, 0.22F, 0.25F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09F, 0.21F, 0.31F, 1.00F);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.28F, 0.56F, 1.00F, 1.00F);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.28F, 0.56F, 1.00F, 1.00F);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37F, 0.61F, 1.00F, 1.00F);
		style.Colors[ImGuiCol_Button] = ImVec4(0.20F, 0.25F, 0.29F, 1.00F);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.28F, 0.56F, 1.00F, 1.00F);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06F, 0.53F, 0.98F, 1.00F);
		style.Colors[ImGuiCol_Header] = ImVec4(0.20F, 0.25F, 0.29F, 0.55F);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26F, 0.59F, 0.98F, 0.80F);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26F, 0.59F, 0.98F, 1.00F);
		style.Colors[ImGuiCol_Separator] = ImVec4(0.20F, 0.25F, 0.29F, 1.00F);
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10F, 0.40F, 0.75F, 0.78F);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.10F, 0.40F, 0.75F, 1.00F);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26F, 0.59F, 0.98F, 0.25F);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26F, 0.59F, 0.98F, 0.67F);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26F, 0.59F, 0.98F, 0.95F);
		style.Colors[ImGuiCol_Tab] = ImVec4(0.11F, 0.15F, 0.17F, 1.00F);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.26F, 0.59F, 0.98F, 0.80F);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.20F, 0.25F, 0.29F, 1.00F);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.11F, 0.15F, 0.17F, 1.00F);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11F, 0.15F, 0.17F, 1.00F);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61F, 0.61F, 0.61F, 1.00F);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00F, 0.43F, 0.35F, 1.00F);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90F, 0.70F, 0.00F, 1.00F);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00F, 0.60F, 0.00F, 1.00F);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26F, 0.59F, 0.98F, 0.35F);
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00F, 1.00F, 0.00F, 0.90F);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26F, 0.59F, 0.98F, 1.00F);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00F, 1.00F, 1.00F, 0.70F);
		style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80F, 0.80F, 0.80F, 0.20F);
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80F, 0.80F, 0.80F, 0.35F);
	}

	void style_green() noexcept {
		auto& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Text] = ImVec4(1.00F, 1.00F, 1.00F, 1.00F);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50F, 0.50F, 0.50F, 1.00F);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.29F, 0.34F, 0.26F, 1.00F);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.29F, 0.34F, 0.26F, 1.00F);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.24F, 0.27F, 0.20F, 1.00F);
		style.Colors[ImGuiCol_Border] = ImVec4(0.54F, 0.57F, 0.51F, 0.50F);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.14F, 0.16F, 0.11F, 0.52F);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.24F, 0.27F, 0.20F, 1.00F);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.27F, 0.30F, 0.23F, 1.00F);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.30F, 0.34F, 0.26F, 1.00F);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.24F, 0.27F, 0.20F, 1.00F);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.29F, 0.34F, 0.26F, 1.00F);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00F, 0.00F, 0.00F, 0.51F);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.24F, 0.27F, 0.20F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.35F, 0.42F, 0.31F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.28F, 0.32F, 0.24F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25F, 0.30F, 0.22F, 1.00F);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.23F, 0.27F, 0.21F, 1.00F);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.59F, 0.54F, 0.18F, 1.00F);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.35F, 0.42F, 0.31F, 1.00F);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.54F, 0.57F, 0.51F, 0.50F);
		style.Colors[ImGuiCol_Button] = ImVec4(0.29F, 0.34F, 0.26F, 0.40F);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.35F, 0.42F, 0.31F, 1.00F);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.54F, 0.57F, 0.51F, 0.50F);
		style.Colors[ImGuiCol_Header] = ImVec4(0.35F, 0.42F, 0.31F, 1.00F);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.35F, 0.42F, 0.31F, 0.6F);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.54F, 0.57F, 0.51F, 0.50F);
		style.Colors[ImGuiCol_Separator] = ImVec4(0.14F, 0.16F, 0.11F, 1.00F);
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.54F, 0.57F, 0.51F, 1.00F);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.59F, 0.54F, 0.18F, 1.00F);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.19F, 0.23F, 0.18F, 0.00F);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.54F, 0.57F, 0.51F, 1.00F);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.59F, 0.54F, 0.18F, 1.00F);
		style.Colors[ImGuiCol_Tab] = ImVec4(0.35F, 0.42F, 0.31F, 1.00F);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.54F, 0.57F, 0.51F, 0.78F);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.59F, 0.54F, 0.18F, 1.00F);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.24F, 0.27F, 0.20F, 1.00F);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35F, 0.42F, 0.31F, 1.00F);
		style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.59F, 0.54F, 0.18F, 1.00F);
		style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20F, 0.20F, 0.20F, 1.00F);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61F, 0.61F, 0.61F, 1.00F);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.59F, 0.54F, 0.18F, 1.00F);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.00F, 0.78F, 0.28F, 1.00F);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00F, 0.60F, 0.00F, 1.00F);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.59F, 0.54F, 0.18F, 1.00F);
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.73F, 0.67F, 0.24F, 1.00F);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.59F, 0.54F, 0.18F, 1.00F);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00F, 1.00F, 1.00F, 0.70F);
		style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80F, 0.80F, 0.80F, 0.20F);
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80F, 0.80F, 0.80F, 0.35F);
	}

	void style_alpha_apply(const float alpha) noexcept {
		auto& style = ImGui::GetStyle();
		style.Alpha = alpha;
	}

	void style_antialiasing_apply(const bool enable_aa) noexcept {
		auto& style = ImGui::GetStyle();
		style.AntiAliasedFill = enable_aa;
		style.AntiAliasedLines = enable_aa;
		style.AntiAliasedLinesUseTex = enable_aa;
	}

	void style_rounding_apply(const float rounding) noexcept {
		auto& style = ImGui::GetStyle();
		style.ChildRounding = rounding;
		style.FrameRounding = rounding;
		style.GrabRounding = rounding;
		style.PopupRounding = rounding;
		style.ScrollbarRounding = rounding;
		style.TabRounding = rounding;
		style.WindowRounding = rounding;
	}

	void style_apply(const SystemStyle style) noexcept {
		switch (style) {
		case SystemStyle::DARK: style_dark();
			return;
		case SystemStyle::BLUE: style_blue();
			return;
		case SystemStyle::GREEN: style_green();
			return;
		case SystemStyle::CHERRY: style_cherry();
			return;
		case SystemStyle::LIGHT: style_light();
		}
	}
} // namespace dce::gui // namespace dce::gui
