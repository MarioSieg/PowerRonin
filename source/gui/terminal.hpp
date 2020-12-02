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

#pragma once

#include "../terminal_sink.hpp"
#include <array>

namespace dce {
	class Runtime;
	class CmdDB;
	class AsyncProtocol;

	namespace gui {
		class Terminal final {
		public:
			static constexpr auto BUFFER_SIZE = 32;
			static constexpr auto COLOR_CRITICAL = 0xFF'88'BB'FF;
			static constexpr auto COLOR_ERROR = 0xFF'36'36'C9;
			static constexpr auto COLOR_INFO = 0xFF'EE'EE'EE;
			static constexpr auto COLOR_TRACE = 0xFF'BB'BB'BB;
			static constexpr auto COLOR_WARN = 0xFF'66'AA'FF;

			auto initialize(const spdlog::sink_ptr& _term_sink) noexcept -> bool;
			void update(bool& _show, Runtime& _rt);
			void clear_buffer();
			[[nodiscard]] auto get_buffer() const noexcept -> const std::array<char, BUFFER_SIZE>&;

		private:
			const TerminalSink<>* sink_ = nullptr;
			std::array<char, BUFFER_SIZE> buffer_ = {};
			std::size_t history_index_ = 0;
			std::size_t warning_messages_count_ = 0;
			std::size_t error_messages_count_ = 0;
			bool scroll_ = true;
		};
	} // namespace gui::widgets // namespace gui::widgets
} // namespace dce // namespace dce
