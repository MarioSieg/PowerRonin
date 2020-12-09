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

#include "../include/dce/proto.hpp"
#include "../include/dce/time_utils.hpp"
#include "../extern/spdlog/include/spdlog/async.h"
#include "../extern/spdlog/include/spdlog/sinks/basic_file_sink.h"
#include "terminal_sink.hpp"

#include <array>
#include <iomanip>
#include <sstream>

namespace dce {
	AsyncProtocol::AsyncProtocol() : AsyncProtocol("engine") { }

	AsyncProtocol::AsyncProtocol(const std::string& _name) {
		auto tm = safe_localtime(std::time(nullptr));
		std::stringstream ss;
		ss << "proto/session-";
		ss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
		ss << ".log";
		spdlog::init_thread_pool(QUEUE_SIZE, THREAD_COUNT);
		const auto thread_pool = spdlog::thread_pool();
		std::array<spdlog::sink_ptr, 2> sinks = {
			std::make_shared<spdlog::sinks::basic_file_sink_mt>(ss.str())
			, std::make_shared<TerminalSink<>>()
		};
		this->core = std::make_shared<spdlog::async_logger>(_name, sinks.begin(), sinks.end(), thread_pool);
		this->file_sink = std::move(sinks[0]);
		this->terminal_sink = std::move(sinks[1]);
	}
} // namespace dce // namespace dce
