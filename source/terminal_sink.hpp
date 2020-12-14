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
#include <string>

namespace dce {
	template <typename Mutex = std::mutex>
	class TerminalSink final : public spdlog::sinks::base_sink<Mutex> {
	public:
		explicit TerminalSink(std::string&& _file_name);
		TerminalSink(const TerminalSink&) = delete;
		TerminalSink(TerminalSink&&) noexcept = default;
		auto operator=(const TerminalSink&) -> TerminalSink& = delete;
		auto operator=(TerminalSink&&) -> TerminalSink& = delete;
		~TerminalSink() override = default;

		[[nodiscard]] auto string_buffer() const noexcept -> const std::vector<std::tuple<std::string, LogLevel>>&;

	protected:
		virtual void sink_it_(const spdlog::details::log_msg& _msg) override;
		virtual void flush_() override;
		std::vector<std::tuple<std::string, LogLevel>> buffer_ = {};
		std::string file_name_ = {};
	};

	template <typename Mutex>
	TerminalSink<Mutex>::TerminalSink(std::string&& _file_name)
		: spdlog::sinks::base_sink<Mutex>(), file_name_(std::move(_file_name)) { }

	template <typename Mutex>
	auto TerminalSink<Mutex>::string_buffer() const noexcept -> const std::vector<std::tuple<std::string, LogLevel>>& {
		return this->buffer_;
	}

	template <typename Mutex>
	void TerminalSink<Mutex>::sink_it_(const spdlog::details::log_msg& _msg) {
		spdlog::memory_buf_t formatted;
		spdlog::sinks::base_sink<Mutex>::formatter_->format(_msg, formatted);
		this->buffer_.emplace_back(std::make_tuple(fmt::to_string(formatted), static_cast<LogLevel>(_msg.level)));
	}

	template <typename Mutex>
	void TerminalSink<Mutex>::flush_() {
		const auto tm = safe_localtime(std::time(nullptr));
		std::stringstream ss;
		ss << "proto/session-";
		ss << this->file_name_;
		ss << '-';
		ss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
		ss << ".log";
		std::ofstream f(ss.str());
		[[likely]] if (f) {
			for (const auto& msg : this->buffer_) {
				f << std::get<0>(msg);
			}
		}
		this->buffer_.clear();
	}
} // namespace dce // namespace dce
