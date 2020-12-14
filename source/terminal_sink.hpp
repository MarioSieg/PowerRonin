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

#pragma once

#include "../extern/spdlog/include/spdlog/sinks/base_sink.h"
#include "../include/dce/proto.hpp"
#include "../include/dce/time_utils.hpp"
#include <mutex>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace dce {
	template <typename Mutex = std::mutex>
	class TerminalSink final : public spdlog::sinks::base_sink<Mutex> {
	public:
		TerminalSink();
		TerminalSink(const TerminalSink&) = delete;
		TerminalSink(TerminalSink&&) noexcept = default;
		auto operator=(const TerminalSink&) -> TerminalSink& = delete;
		auto operator=(TerminalSink&&) -> TerminalSink& = delete;
		~TerminalSink() override = default;

		[[nodiscard]] auto string_buffer() const noexcept -> const std::vector<std::tuple<std::string, LogLevel>>&;

	protected:
		virtual void sink_it_(const spdlog::details::log_msg& msg) override;
		virtual void flush_() override;
		std::vector<std::tuple<std::string, LogLevel>> buffer = {};
	};

	template <typename Mutex>
	TerminalSink<Mutex>::TerminalSink() : spdlog::sinks::base_sink<Mutex>() { }

	template <typename Mutex>
	auto TerminalSink<Mutex>::string_buffer() const noexcept -> const std::vector<std::tuple<std::string, LogLevel>>& {
		return this->buffer;
	}

	template <typename Mutex>
	void TerminalSink<Mutex>::sink_it_(const spdlog::details::log_msg& msg) {
		spdlog::memory_buf_t formatted;
		spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
		this->buffer.emplace_back(std::make_tuple(fmt::to_string(formatted), static_cast<LogLevel>(msg.level)));
	}

	template <typename Mutex>
	void TerminalSink<Mutex>::flush_() {
		const auto tm = safe_localtime(std::time(nullptr));
		std::stringstream ss;
		ss << "proto/session-";
		ss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
		ss << ".log";
		std::ofstream f(ss.str());
		[[likely]] if(f) {
			for(const auto& msg : this->buffer) {
				f << std::get<0>(msg);
			}
		}
		this->buffer.clear();
	}
} // namespace dce // namespace dce
