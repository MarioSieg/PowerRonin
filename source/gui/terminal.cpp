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

#include "../../include/power_ronin/runtime.hpp"

#include "terminal.hpp"
#include "font_headers.hpp"
#include "gui_headers.hpp"
#include "window_names.hpp"

using namespace ImGui;

namespace power_ronin
{
	void (*TERMINAL_UPDATE)() = nullptr;
}

namespace power_ronin::gui
{
	void Terminal::update(bool& _show, Runtime& _rt)
	{
		SetNextWindowSize({800, 600}, ImGuiCond_FirstUseEver);
		if (Begin(TERMINAL_NAME, &_show, ImGuiWindowFlags_NoScrollbar)) [[likely]]
		{
			const auto footer_height_to_reserve = GetStyle().ItemSpacing.y + GetFrameHeightWithSpacing();
			const auto print_sink = [this](const TerminalSink<>* const _sink)
			{
				for (const auto& msg : _sink->string_buffer())
				{
					switch (std::get<1>(msg))
					{
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
					Spacing();
					TextUnformatted(std::get<0>(msg).c_str());
					PopStyleColor();
				}
			};
			if (BeginChild("", {.0, -footer_height_to_reserve}, false)) [[likely]]
			{
				PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));

				if (this->show_scripting_protocol_) [[likely]]
				{
					print_sink(this->scripting_protocol_);
				}
				else
				{
					print_sink(this->system_protocol_);
				}

				PopStyleVar();
			}
			if (this->scroll_) [[unlikely]]
			{
				SetScrollHereY(1.F);
			}

			EndChild();
			Spacing();
			Separator();

			/* Warning messages info. */
			{
				PushStyleColor(ImGuiCol_Text, COLOR_WARN);
				Text(ICON_FA_EXCLAMATION_TRIANGLE " %zu", this->warning_messages_count_);
				if (IsItemHovered()) [[unlikely]]
				{
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
				if (IsItemHovered()) [[unlikely]]
				{
					BeginTooltip();
					Text("%zu error messages", this->error_messages_count_);
					EndTooltip();
				}
				this->error_messages_count_ = 0;
				PopStyleColor();
			}

			SameLine();

			/* Show scripting output. */
			{
				Checkbox("##out", &this->show_scripting_protocol_);
				if (IsItemHovered()) [[unlikely]]
				{
					BeginTooltip();
					TextUnformatted("Show scripting protocol instead of system protocol");
					EndTooltip();
				}
			}

			SameLine();

			/* Input text field. */
			{
				PushItemWidth(GetWindowSize().x);
				constexpr auto flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank;
				const auto get_input_ok = InputText("##in", this->buffer_, sizeof this->buffer_, flags);
				const auto is_input_valid = *this->buffer_ != '\0';

				if (this->scroll_) [[unlikely]]
				{
					SetKeyboardFocusHere(-1);
					this->scroll_ = false;
				}

				if (get_input_ok) [[unlikely]]
				{
					if (is_input_valid) [[likely]]
					{
						_rt.terminal_hook()(this->buffer_);
						memset(this->buffer_, 0, sizeof this->buffer_);
						this->scroll_ = true;
						this->history_index_ = 0;
						SetScrollHere(1.F);
					}
					else
					{
						_rt.protocol().error("Invalid input! Type \"help\"!");
					}
				}
				PopItemWidth();
			}
		}
		End();
	}

	auto Terminal::initialize(const AsyncProtocol& _system_protocol,
	                          const AsyncProtocol& _scripting_protocol) noexcept -> bool
	{
		if (_system_protocol.get_logger()->sinks().empty() || _scripting_protocol.get_logger()->sinks().
		                                                                          empty()) [[unlikely]]
		{
			return false;
		}
		this->system_protocol_ = dynamic_cast<const TerminalSink<>*>(&*_system_protocol.get_logger()->sinks()[0]);
		this->scripting_protocol_ = dynamic_cast<const TerminalSink<>*>(&*_scripting_protocol.get_logger()->sinks()[0]);
		return this->system_protocol_ && this->scripting_protocol_;
	}
} // namespace power_ronin::gui::widgets // namespace power_ronin::gui::widgets
