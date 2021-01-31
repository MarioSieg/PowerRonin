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

#include "profiler.hpp"

#include "../font_headers.hpp"
#include "../gui_headers.hpp"
#include "../../include/power_ronin/diagnostics.hpp"
#include "../../include/power_ronin/chrono.hpp"
#include "../window_names.hpp"
#include <chrono>
#include <cinttypes>
#include <string>

using namespace ImGui;
using namespace ImPlot;

namespace PowerRonin::Interface::widgets
{
	void Profiler::update(bool& _show, const Diagnostics& _diag, const Chrono& _chrono) const
	{
		if (Begin(PROFILER_NAME, &_show, ImGuiWindowFlags_AlwaysAutoResize)) [[likely]]
		{
			if (CollapsingHeader("General", ImGuiTreeNodeFlags_DefaultOpen)) [[likely]]
			{
				Text("Frequency: %f", _chrono.Frequency);
				Text("Clock cycles: %u", _chrono.Cycles);

				const auto dur = std::chrono::system_clock::now() - _chrono.StartTime;
				const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(dur).count();
				const auto minutes = std::chrono::duration_cast<std::chrono::minutes>(dur).count();
				const auto hours = std::chrono::duration_cast<std::chrono::hours>(dur).count();
				Text("Clock: %02" PRIu64 ":%02" PRIu64 ":%02" PRIu64, hours % UINT64_C(60), minutes % UINT64_C(60)
				     , seconds % UINT64_C(60));

				Text("Delta clock: %f", _chrono.DeltaTime);
				Text("Monotonic clock: %f", _chrono.Time);
				Text("Submit clocks: CPU %.3f, GPU %.3f, Max GPU latency: %" PRIu32, _chrono.SubmitCpu,
				     _chrono.SubmitGpu
				     , _chrono.MaxGpuLatency);
			}
			const auto pie_size = ImVec2{250, 250};
			char total_buf[64];
			if (CollapsingHeader("GPU")) [[likely]]
			{
				snprintf(total_buf, sizeof total_buf, "Total: %.1fMB"
				         , static_cast<double>(_diag.Graphics.MaxVram) / 1024. / 1024.);
				if (BeginPlot("##vram", ICON_FA_MEMORY" VRAM", total_buf, pie_size, ImPlotFlags_NoMousePos
				              , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) [[likely]]
				{
					constexpr const char* const labels[] = {"Available", "Used"};
					const float data[] = {
						static_cast<float>(_diag.Graphics.MaxVram - _diag.Graphics.UsedVram) / 1024.f / 1024.f,
						static_cast<float>(_diag.Graphics.UsedVram) / 1024.f / 1024.f
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.1fMB");
					EndPlot();
					if (IsItemHovered()) [[unlikely]]
					{
						BeginTooltip();
						TextUnformatted("Video memory (VRAM) usage");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.Graphics.MaxDrawCalls);
				if (BeginPlot("##draws", ICON_FA_PENCIL" Draws", total_buf, pie_size, ImPlotFlags_NoMousePos
				              , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) [[likely]]
				{
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.Graphics.MaxDrawCalls - _diag.Graphics.UsedDrawCalls, _diag.Graphics.UsedDrawCalls
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					if (IsItemHovered()) [[unlikely]]
					{
						BeginTooltip();
						TextUnformatted("Amount of draw calls used/available");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.Graphics.MaxBlitCalls);
				if (BeginPlot("##blits", ICON_FA_LAYER_GROUP" Blits", total_buf, pie_size,
				              ImPlotFlags_NoMousePos
				              , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) [[likely]]
				{
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.Graphics.MaxBlitCalls - _diag.Graphics.UsedBlitCalls, _diag.Graphics.UsedBlitCalls
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					if (IsItemHovered()) [[unlikely]]
					{
						BeginTooltip();
						TextUnformatted("Amount of blit calls used/available");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.Graphics.MaxTextures);
				if (BeginPlot("##textures", ICON_FA_IMAGE " Textures", total_buf, pie_size,
				              ImPlotFlags_NoMousePos
				              , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) [[likely]]
				{
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.Graphics.MaxTextures - _diag.Graphics.UsedTextures, _diag.Graphics.UsedTextures
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					if (IsItemHovered()) [[unlikely]]
					{
						BeginTooltip();
						TextUnformatted("Amount of textures used/available");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.Graphics.MaxShaders);
				if (BeginPlot("##shaders", ICON_FA_EYE " Shaders", total_buf, pie_size,
				              ImPlotFlags_NoMousePos
				              , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) [[likely]]
				{
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.Graphics.MaxShaders - _diag.Graphics.UsedShaders, _diag.Graphics.UsedShaders
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					if (IsItemHovered()) [[unlikely]]
					{
						BeginTooltip();
						TextUnformatted("Amount of shaders used/available");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.Graphics.MaxShaders);
				if (BeginPlot("##programs", ICON_FA_PAINT_ROLLER" Shader Programs", total_buf, pie_size
				              , ImPlotFlags_NoMousePos, ImPlotAxisFlags_NoDecorations,
				              ImPlotAxisFlags_NoDecorations)) [[likely]]
				{
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.Graphics.MaxPrograms - _diag.Graphics.UsedPrograms, _diag.Graphics.UsedPrograms
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					if (IsItemHovered()) [[unlikely]]
					{
						BeginTooltip();
						TextUnformatted("Amount of shader programs used/available");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.Graphics.MaxUniforms);
				if (BeginPlot("##uniforms", ICON_FA_ETHERNET" Uniforms", total_buf, pie_size,
				              ImPlotFlags_NoMousePos
				              , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) [[likely]]
				{
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.Graphics.MaxUniforms - _diag.Graphics.UsedUniforms, _diag.Graphics.UsedUniforms
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					if (IsItemHovered()) [[unlikely]]
					{
						BeginTooltip();
						TextUnformatted("Amount of uniforms calls used/available");
						EndTooltip();
					}
				}

				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.Graphics.MaxVertexBuffers);
				if (BeginPlot("##vbs", ICON_FA_TRIANGLE " Vertex Buffers", total_buf, pie_size,
				              ImPlotFlags_NoMousePos
				              , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) [[likely]]
				{
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.Graphics.MaxVertexBuffers - _diag.Graphics.UsedVertexBuffers,
						_diag.Graphics.UsedVertexBuffers
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					if (IsItemHovered()) [[unlikely]]
					{
						BeginTooltip();
						TextUnformatted("Amount of vertex buffers used/available to store geometry data");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.Graphics.MaxIndexBuffers);
				if (BeginPlot("##ibs", ICON_FA_SIGMA " Index Buffers", total_buf, pie_size,
				              ImPlotFlags_NoMousePos
				              , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) [[likely]]
				{
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.Graphics.MaxIndexBuffers - _diag.Graphics.UsedIndexBuffers,
						_diag.Graphics.UsedIndexBuffers
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					if (IsItemHovered()) [[unlikely]]
					{
						BeginTooltip();
						TextUnformatted("Amount of index buffers used/available to store geometry index data");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.Graphics.MaxDynamicVertexBuffers);
				if (BeginPlot("##tvbs", ICON_FA_TRIANGLE " Dynamic Vertex Buffers", total_buf, pie_size
				              , ImPlotFlags_NoMousePos, ImPlotAxisFlags_NoDecorations,
				              ImPlotAxisFlags_NoDecorations)) [[likely]]
				{
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.Graphics.MaxDynamicVertexBuffers - _diag.Graphics.UsedDynamicVertexBuffers,
						_diag.Graphics.UsedDynamicVertexBuffers
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					if (IsItemHovered()) [[unlikely]]
					{
						BeginTooltip();
						TextUnformatted("Amount of dynamic vertex buffers used/available to store geometry data");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.Graphics.MaxDynamicIndexBuffers);
				if (BeginPlot("##tibs", ICON_FA_SIGMA " Dynamic Index Buffers", total_buf, pie_size
				              , ImPlotFlags_NoMousePos, ImPlotAxisFlags_NoDecorations,
				              ImPlotAxisFlags_NoDecorations)) [[likely]]
				{
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.Graphics.MaxDynamicIndexBuffers - _diag.Graphics.UsedDynamicIndexBuffers,
						_diag.Graphics.UsedDynamicIndexBuffers
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					if (IsItemHovered()) [[unlikely]]
					{
						BeginTooltip();
						TextUnformatted("Amount of dynamic index buffers used/available to store geometry index data");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.Graphics.MaxFrameBuffers);
				if (BeginPlot("##fbs", ICON_FA_IMAGES " Frame Buffers", total_buf, pie_size,
				              ImPlotFlags_NoMousePos
				              , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) [[likely]]
				{
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.Graphics.MaxFrameBuffers - _diag.Graphics.UsedFrameBuffers,
						_diag.Graphics.UsedFrameBuffers
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					if (IsItemHovered()) [[unlikely]]
					{
						BeginTooltip();
						TextUnformatted("Amount of frame buffers used/available");
						EndTooltip();
					}
				}
			}
		}
		End();
	}
} // namespace PowerRonin::gui::widgets // namespace PowerRonin::gui::widgets

#endif
