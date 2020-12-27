#include "../include/dce/proto.hpp"
#include "../include/dce/time_utils.hpp"
#include "../extern/spdlog/include/spdlog/async.h"
#include "../extern/spdlog/include/spdlog/sinks/basic_file_sink.h"
#include "terminal_sink.hpp"

#include <array>
#include <iomanip>
#include <sstream>

namespace dce {
	AsyncProtocol::AsyncProtocol() : AsyncProtocol("engine") {
	}

	AsyncProtocol::AsyncProtocol(const std::string& _name) {
		[[unlikely]] if (!spdlog::thread_pool()) {
			spdlog::init_thread_pool(QUEUE_SIZE, THREAD_COUNT);
		}
		const auto thread_pool = spdlog::thread_pool();
		auto name = _name;
		this->core_ = std::make_shared<spdlog::async_logger>(_name, std::make_shared<TerminalSink<>>(std::move(name)),
		                                                     thread_pool);
	}
} // namespace dce // namespace dce
