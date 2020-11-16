// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: terminal.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "../../terminal_sink.hpp"
#include <array>

namespace dce {
	class State;
	class CmdDB;
	class AsyncProtocol;

	namespace gui::widgets {
		class Terminal final {
		public:
			static constexpr auto BUFFER_SIZE = 32;
			static constexpr auto COLOR_CRITICAL = 0xFF'88'BB'FF;
			static constexpr auto COLOR_ERROR = 0xFF'36'36'C9;
			static constexpr auto COLOR_INFO = 0xFF'EE'EE'EE;
			static constexpr auto COLOR_TRACE = 0xFF'BB'BB'BB;
			static constexpr auto COLOR_WARN = 0xFF'66'AA'FF;

			auto initialize(const spdlog::sink_ptr &_term_sink) noexcept -> bool;
			void update(bool &_show, State &_state);
			void clear_buffer();
			[[nodiscard]] auto get_buffer() const noexcept -> const std::array<char, BUFFER_SIZE>&;

		private:
			const TerminalSink<> *sink_ = nullptr;
			std::array<char, BUFFER_SIZE> buffer_ = {};
			std::size_t history_index_ = 0;
			std::size_t warning_messages_count_ = 0;
			std::size_t error_messages_count_ = 0;
			bool scroll_ = true;
		};
	} // namespace gui::widgets // namespace gui::widgets
} // namespace dce // namespace dce
