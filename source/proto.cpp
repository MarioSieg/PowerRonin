#include "../Include/PowerRonin/Protocol.hpp"
#include "../Include/PowerRonin/TimeUtils.hpp"
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
