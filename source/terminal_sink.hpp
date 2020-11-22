// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: terminal_sink.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "../extern/spdlog/include/spdlog/sinks/base_sink.h"
#include "../include/dce/proto.hpp"
#include <mutex>
#include <string>
#include <tuple>
#include <vector>

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
	void TerminalSink<Mutex>::flush_() { }
} // namespace dce // namespace dce
