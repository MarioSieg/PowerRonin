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
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "profiler.hpp"

#include "../font_headers.hpp"
#include "../gui_headers.hpp"
#include "../../include/dce/diagnostics.hpp"
#include "../../include/dce/chrono.hpp"
#include "../window_names.hpp"
#include <chrono>
#include <cinttypes>
#include <string>

using namespace ImGui;
using namespace ImPlot;

namespace dce::gui::widgets {
	void Profiler::update(bool& _show, const Diagnostics& _diag, const Chrono& _chrono) const {
		[[likely]] if (Begin(PROFILER_NAME, &_show, ImGuiWindowFlags_AlwaysAutoResize)) {
			[[likely]] if (CollapsingHeader("General", ImGuiTreeNodeFlags_DefaultOpen)) {
				Text("Frequency: %f", _chrono.frequency);
				Text("Clock cycles: %u", _chrono.cycles);

				const auto dur = std::chrono::system_clock::now() - _chrono.start_time;
				const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(dur).count();
				const auto minutes = std::chrono::duration_cast<std::chrono::minutes>(dur).count();
				const auto hours = std::chrono::duration_cast<std::chrono::hours>(dur).count();
				Text("Clock: %02" PRIu64 ":%02" PRIu64 ":%02" PRIu64, hours % UINT64_C(60), minutes % UINT64_C(60)
				     , seconds % UINT64_C(60));

				Text("Delta clock: %f", _chrono.delta_time);
				Text("Monotonic clock: %f", _chrono.time);
				Text("Submit clocks: CPU %.3f, GPU %.3f, Max GPU latency: %" PRIu32, _chrono.submit_cpu, _chrono.submit_gpu
				     , _chrono.max_gpu_latency);
			}
			const auto pie_size = ImVec2{250, 250};
			char total_buf[64];
			[[likely]] if (CollapsingHeader("GPU")) {
				snprintf(total_buf, sizeof total_buf, "Total: %.1fMB"
				         , static_cast<double>(_diag.graphics.max_vram) / 1024. / 1024.);
				[[likely]] if (BeginPlot("##vram", ICON_FA_MEMORY" VRAM", total_buf, pie_size, ImPlotFlags_NoMousePos
				                         , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) {
					constexpr const char* const labels[] = {"Available", "Used"};
					const float data[] = {
						static_cast<float>(_diag.graphics.max_vram - _diag.graphics.used_vram) / 1024.f / 1024.f
						, static_cast<float>(_diag.graphics.used_vram) / 1024.f / 1024.f
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.1fMB");
					EndPlot();
					[[unlikely]] if (IsItemHovered()) {
						BeginTooltip();
						TextUnformatted("Video memory (VRAM) usage");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.graphics.max_draw_calls);
				[[likely]] if (BeginPlot("##draws", ICON_FA_PENCIL" Draws", total_buf, pie_size, ImPlotFlags_NoMousePos
				                         , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) {
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.graphics.max_draw_calls - _diag.graphics.used_draw_calls
						, _diag.graphics.used_draw_calls
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					[[unlikely]] if (IsItemHovered()) {
						BeginTooltip();
						TextUnformatted("Amount of draw calls used/available");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.graphics.max_blit_calls);
				[[likely]] if (BeginPlot("##blits", ICON_FA_LAYER_GROUP" Blits", total_buf, pie_size, ImPlotFlags_NoMousePos
				                         , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) {
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.graphics.max_blit_calls - _diag.graphics.used_blit_calls
						, _diag.graphics.used_blit_calls
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					[[unlikely]] if (IsItemHovered()) {
						BeginTooltip();
						TextUnformatted("Amount of blit calls used/available");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.graphics.max_textures);
				[[likely]] if (BeginPlot("##textures", ICON_FA_IMAGE " Textures", total_buf, pie_size, ImPlotFlags_NoMousePos
				                         , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) {
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.graphics.max_textures - _diag.graphics.used_textures
						, _diag.graphics.used_textures
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					[[unlikely]] if (IsItemHovered()) {
						BeginTooltip();
						TextUnformatted("Amount of textures used/available");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.graphics.max_shaders);
				[[likely]] if (BeginPlot("##shaders", ICON_FA_EYE " Shaders", total_buf, pie_size, ImPlotFlags_NoMousePos
				                         , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) {
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.graphics.max_shaders - _diag.graphics.used_shaders
						, _diag.graphics.used_shaders
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					[[unlikely]] if (IsItemHovered()) {
						BeginTooltip();
						TextUnformatted("Amount of shaders used/available");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.graphics.max_shaders);
				[[likely]] if (BeginPlot("##programs", ICON_FA_PAINT_ROLLER" Shader Programs", total_buf, pie_size
				                         , ImPlotFlags_NoMousePos, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) {
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.graphics.max_programs - _diag.graphics.used_programs
						, _diag.graphics.used_programs
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					[[unlikely]] if (IsItemHovered()) {
						BeginTooltip();
						TextUnformatted("Amount of shader programs used/available");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.graphics.max_uniforms);
				[[likely]] if (BeginPlot("##uniforms", ICON_FA_ETHERNET" Uniforms", total_buf, pie_size, ImPlotFlags_NoMousePos
				                         , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) {
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.graphics.max_uniforms - _diag.graphics.used_uniforms
						, _diag.graphics.used_uniforms
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					[[unlikely]] if (IsItemHovered()) {
						BeginTooltip();
						TextUnformatted("Amount of uniforms calls used/available");
						EndTooltip();
					}
				}

				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.graphics.max_vertex_buffers);
				[[likely]] if (BeginPlot("##vbs", ICON_FA_TRIANGLE " Vertex Buffers", total_buf, pie_size, ImPlotFlags_NoMousePos
				                         , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) {
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.graphics.max_vertex_buffers - _diag.graphics.used_vertex_buffers
						, _diag.graphics.used_vertex_buffers
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					[[unlikely]] if (IsItemHovered()) {
						BeginTooltip();
						TextUnformatted("Amount of vertex buffers used/available to store geometry data");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.graphics.max_index_buffers);
				[[likely]] if (BeginPlot("##ibs", ICON_FA_SIGMA " Index Buffers", total_buf, pie_size, ImPlotFlags_NoMousePos
				                         , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) {
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.graphics.max_index_buffers - _diag.graphics.used_index_buffers
						, _diag.graphics.used_index_buffers
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					[[unlikely]] if (IsItemHovered()) {
						BeginTooltip();
						TextUnformatted("Amount of index buffers used/available to store geometry index data");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.graphics.max_dynamic_vertex_buffers);
				[[likely]] if (BeginPlot("##tvbs", ICON_FA_TRIANGLE " Dynamic Vertex Buffers", total_buf, pie_size
				                         , ImPlotFlags_NoMousePos, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) {
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.graphics.max_dynamic_vertex_buffers - _diag.graphics.used_dynamic_vertex_buffers
						, _diag.graphics.used_dynamic_vertex_buffers
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					[[unlikely]] if (IsItemHovered()) {
						BeginTooltip();
						TextUnformatted("Amount of dynamic vertex buffers used/available to store geometry data");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.graphics.max_dynamic_index_buffers);
				[[likely]] if (BeginPlot("##tibs", ICON_FA_SIGMA " Dynamic Index Buffers", total_buf, pie_size
				                         , ImPlotFlags_NoMousePos, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) {
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.graphics.max_dynamic_index_buffers - _diag.graphics.used_dynamic_index_buffers
						, _diag.graphics.used_dynamic_index_buffers
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					[[unlikely]] if (IsItemHovered()) {
						BeginTooltip();
						TextUnformatted("Amount of dynamic index buffers used/available to store geometry index data");
						EndTooltip();
					}
				}
				SameLine();
				snprintf(total_buf, sizeof total_buf, "Total: %zu", _diag.graphics.max_frame_buffers);
				[[likely]] if (BeginPlot("##fbs", ICON_FA_IMAGES " Frame Buffers", total_buf, pie_size, ImPlotFlags_NoMousePos
				                         , ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations)) {
					constexpr const char* const labels[] = {"Available", "Used"};
					const std::size_t data[] = {
						_diag.graphics.max_frame_buffers - _diag.graphics.used_frame_buffers
						, _diag.graphics.used_frame_buffers
					};
					PlotPieChart(labels, data, sizeof data / sizeof *data, .5, .5, .4, false, "%.0f");
					EndPlot();
					[[unlikely]] if (IsItemHovered()) {
						BeginTooltip();
						TextUnformatted("Amount of frame buffers used/available");
						EndTooltip();
					}
				}
			}
		}
		End();
	}
} // namespace dce::gui::widgets // namespace dce::gui::widgets
