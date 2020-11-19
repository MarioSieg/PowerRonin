// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: proto.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "../include/dce/proto.hpp"
#include "terminal_sink.hpp"
#include "../extern/spdlog/include/spdlog/async.h"
#include "../extern/spdlog/include/spdlog/sinks/basic_file_sink.h"

#include <array>
#include <iomanip>
#include <sstream>

namespace dce {
	AsyncProtocol::AsyncProtocol() : AsyncProtocol("engine") { }

	AsyncProtocol::AsyncProtocol(const std::string &_name) {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		std::stringstream ss;
		ss << "proto/session-";
		ss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
		ss << ".log";
		spdlog::init_thread_pool(QUEUE_SIZE, THREAD_COUNT);
		const auto thread_pool = spdlog::thread_pool();
		std::array<spdlog::sink_ptr, 2> sinks = {
			std::make_shared<spdlog::sinks::basic_file_sink_mt>(ss.str()), std::make_shared<TerminalSink<>>()
		};
		this->core = std::make_shared<spdlog::async_logger>(_name, sinks.begin(), sinks.end(), thread_pool);
		this->file_sink = std::move(sinks[0]);
		this->terminal_sink = std::move(sinks[1]);
	}
} // namespace dce // namespace dce
