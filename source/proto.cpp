#include "../include/power_ronin/proto.hpp"
#include "../include/power_ronin/time_utils.hpp"
#include "../extern/spdlog/include/spdlog/async.h"
#include "../extern/spdlog/include/spdlog/sinks/basic_file_sink.h"
#include "terminal_sink.hpp"

#include <array>
#include <iomanip>
#include <sstream>

namespace power_ronin
{
	AsyncProtocol::AsyncProtocol() : AsyncProtocol("engine") { }

	AsyncProtocol::AsyncProtocol(const std::string& _name)
	{
		if (!spdlog::thread_pool()) [[unlikely]]
		{
			spdlog::init_thread_pool(QUEUE_SIZE, THREAD_COUNT);
		}
		const auto thread_pool = spdlog::thread_pool();
		auto name = _name;
		this->core_ = std::make_shared<spdlog::async_logger>(_name, std::make_shared<TerminalSink<>>(std::move(name)),
		                                                     thread_pool);
	}
} // namespace power_ronin // namespace power_ronin
