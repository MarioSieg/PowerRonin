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

#include "../include/power_ronin/proto.hpp"
#include "../include/power_ronin/time_utils.hpp"
#include "../extern/spdlog/include/spdlog/async.h"
#include "../extern/spdlog/include/spdlog/sinks/basic_file_sink.h"
#include "terminal_sink.hpp"

#include <array>
#include <iomanip>
#include <sstream>

namespace PowerRonin
{
	AsyncProtocol::AsyncProtocol() : AsyncProtocol("engine") { }

	AsyncProtocol::AsyncProtocol(const std::string& _name)
	{
		if (!spdlog::thread_pool()) [[unlikely]]
		{
			spdlog::init_thread_pool(QueueSize, ThreadCount);
		}
		const auto thread_pool = spdlog::thread_pool();
		auto name = _name;
		this->core = std::make_shared<spdlog::async_logger>(_name, std::make_shared<TerminalSink<>>(std::move(name)),
		                                                     thread_pool);
	}
} // namespace PowerRonin // namespace PowerRonin
