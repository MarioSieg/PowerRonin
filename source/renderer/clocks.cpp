// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: clocks.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "clocks.hpp"
#include "../../include/dce/chrono.hpp"
#include "../sysclock.hpp"
#include "../../extern/bgfx/bgfx/include/bgfx/bgfx.h"

namespace dce::renderer {
	auto update_clocks(Chrono &_chrono, const std::uint64_t _prev) noexcept -> std::uint64_t {
		++_chrono.cycles;
		const auto now = get_high_precision_counter();
		const auto frame_time = now - _prev;
		_chrono.frequency = static_cast<double>(get_high_precision_frequency());
		_chrono.delta_time = static_cast<double>(frame_time) / _chrono.frequency;
		_chrono.time += _chrono.delta_time;

		const auto &stats = *bgfx::getStats();
		_chrono.cpu_ms = 1000. / static_cast<double>(stats.cpuTimerFreq);
		_chrono.gpu_ms = 1000. / static_cast<double>(stats.gpuTimerFreq);
		_chrono.frame_ms = static_cast<double>(stats.cpuTimeFrame) * _chrono.cpu_ms;
		const auto submit_cpu = static_cast<double>(stats.cpuTimeEnd - stats.cpuTimeBegin) * _chrono.cpu_ms;
		_chrono.submit_cpu = submit_cpu;
		const auto submit_gpu = static_cast<double>(stats.gpuTimeEnd - stats.gpuTimeBegin) * _chrono.gpu_ms;
		_chrono.submit_gpu = submit_gpu;
		_chrono.max_latency = bgfx::getStats()->maxGpuLatency;
		return now;
	}
}
