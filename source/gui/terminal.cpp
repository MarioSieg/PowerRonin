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

#include "../../include/dce/runtime.hpp"

#include "terminal.hpp"
#include "font_headers.hpp"
#include "gui_headers.hpp"
#include "window_names.hpp"

#include <algorithm>

using namespace ImGui;

namespace dce::gui {
	void Terminal::clear_buffer() {
		this->buffer_.fill(0);
	}

	auto Terminal::get_buffer() const noexcept -> const std::array<char, BUFFER_SIZE>& {
		return this->buffer_;
	}

	void Terminal::update(bool& _show, Runtime& _rt) {
		SetNextWindowSize({800, 600}, ImGuiCond_FirstUseEver);
		[[likely]] if (Begin(TERMINAL_NAME, &_show, ImGuiWindowFlags_NoScrollbar)) {
			const auto footer_height_to_reserve = GetStyle().ItemSpacing.y + GetFrameHeightWithSpacing();
			if (BeginChild("", {.0, -footer_height_to_reserve}, false)) {
				PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));

				[[likely]] if (this->sink_ != nullptr) {
					for (const auto& msg : sink_->string_buffer()) {
						switch (std::get<1>(msg)) {
							[[unlikely]] case LogLevel::ERROR: PushStyleColor(ImGuiCol_Text, COLOR_ERROR);
							++this->error_messages_count_;
							break;
							[[likely]] case LogLevel::INFO: PushStyleColor(ImGuiCol_Text, COLOR_INFO);
							break;
							[[unlikely]] case LogLevel::DEBUG:
						case LogLevel::TRACE: PushStyleColor(ImGuiCol_Text, COLOR_TRACE);
							break;
							[[unlikely]] case LogLevel::CRITICAL:
						case LogLevel::WARN: PushStyleColor(ImGuiCol_Text, COLOR_WARN);
							++this->warning_messages_count_;
							break;
						default: case LogLevel::OFF: ;
						}
						TextUnformatted(std::get<0>(msg).c_str());
						PopStyleColor();
					}
				}
				else {
					PushStyleColor(ImGuiCol_Text, 0xFF'66'66'FF);
					TextUnformatted("Terminal sink pointer is nullptr!");
					PopStyleColor();
				}

				PopStyleVar();
			}
			[[unlikely]] if (this->scroll_) {
				SetScrollHereY(1.F);
			}

			EndChild();
			Spacing();
			Separator();

			/* Warning messages info. */
			{
				PushStyleColor(ImGuiCol_Text, COLOR_WARN);
				Text(ICON_FA_EXCLAMATION_TRIANGLE " %zu", this->warning_messages_count_);
				[[unlikely]] if (IsItemHovered()) {
					BeginTooltip();
					Text("%zu warning messages", this->warning_messages_count_);
					EndTooltip();
				}
				this->warning_messages_count_ = 0;
				PopStyleColor();
			}

			SameLine();

			/* Error messages info. */
			{
				PushStyleColor(ImGuiCol_Text, COLOR_ERROR);
				Text(ICON_FA_BOMB " %zu", this->error_messages_count_);
				[[unlikely]] if (IsItemHovered()) {
					BeginTooltip();
					Text("%zu error messages", this->error_messages_count_);
					EndTooltip();
				}
				this->error_messages_count_ = 0;
				PopStyleColor();
			}

			SameLine();

			/* History button. */
			{
				const auto& history = _rt.command_db().get_history();
				PushStyleColor(ImGuiCol_Button, 0x00000000);
				const bool history_forward = Button(ICON_FA_ARROW_UP);
				[[unlikely]] if (IsItemHovered()) {
					BeginTooltip();
					TextUnformatted("Load previous command");
					EndTooltip();
				}
				[[unlikely]] if (history_forward && !history.empty()) {
					const auto i = std::clamp<std::size_t>(history.size() - this->history_index_ - 1, 0, history.size() - 1);
					const auto& prev_command = history[i];
					prev_command.copy(this->buffer_.data(), BUFFER_SIZE);
					++this->history_index_;
					if (this->history_index_ >= history.size()) {
						this->history_index_ = 0;
					}
					SetKeyboardFocusHere(1);
				}

				PopStyleColor(); /* PushStyleColor(ImGuiCol_Button, 0x00000000); */
			}

			SameLine();

			/* Input text field. */
			{
				PushItemWidth(GetWindowSize().x);
				constexpr auto flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank;
				const auto get_input_ok = InputText("##in", this->buffer_.data(), sizeof this->buffer_, flags);
				const auto is_input_valid = *this->buffer_.data() != '\0';

				[[unlikely]] if (this->scroll_) {
					SetKeyboardFocusHere(-1);
					this->scroll_ = false;
				}

				[[unlikely]] if (get_input_ok) {
					if (is_input_valid) {
						auto dyn_str = std::string(this->buffer_.begin(), this->buffer_.end());
						switch (auto& proto = _rt.protocol(); _rt.command_db().analyze_and_call(_rt, std::move(dyn_str))) {
						case CommandExecutionResult::COMMAND_DOES_NOT_EXIST: proto.error("Command does not exist!");
							break;
						case CommandExecutionResult::ARGS_SEPARATOR_MISSING: proto.error(
								"Missing '{}' as separator!", CmdDB::ARGUMENT_SEPARATOR);
							break;
						case CommandExecutionResult::NO_ARGS_PROVIDED: proto.error("Missing arguments!");
							break;
						case CommandExecutionResult::COMMAND_FUNCTOR_FAILED: proto.error("Command execution failed!");
							break;
						case CommandExecutionResult::OK: ;
						}
						this->clear_buffer();
						this->scroll_ = true;
						this->history_index_ = 0;
						SetScrollHere(1.F);
					}
					else {
						_rt.protocol().error("Invalid input! Type \"help\"!");
					}
				}
				PopItemWidth();
			}
		}
		End();
	}

	auto Terminal::initialize(const spdlog::sink_ptr& _term_sink) noexcept -> bool {
		this->sink_ = dynamic_cast<const TerminalSink<>*>(&*_term_sink);
		return this->sink_ != nullptr;
	}
} // namespace dce::gui::widgets // namespace dce::gui::widgets
