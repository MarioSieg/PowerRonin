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

#include "clocks.hpp"
#include "../../include/power_ronin/chrono.hpp"
#include "../sysclock.hpp"
#include "../../extern/bgfx/bgfx/include/bgfx/bgfx.h"

namespace power_ronin::renderer
{
	auto update_clocks(Chrono& _chrono, const std::uint64_t _prev) noexcept -> std::uint64_t
	{
		const auto& stats = *bgfx::getStats();
		const auto now = get_high_precision_counter();

		_chrono.frequency = static_cast<double>(get_high_precision_frequency());
		_chrono.delta_time = static_cast<double>(get_high_precision_counter() - _prev) / _chrono.frequency;
		_chrono.time += _chrono.delta_time;
		_chrono.cpu_ms = 1000. / static_cast<double>(stats.cpuTimerFreq);
		_chrono.gpu_ms = 1000. / static_cast<double>(stats.gpuTimerFreq);
		_chrono.frame_time = static_cast<double>(stats.cpuTimeFrame) * _chrono.cpu_ms;
		_chrono.submit_cpu = static_cast<double>(stats.cpuTimeEnd - stats.cpuTimeBegin) * _chrono.cpu_ms;
		_chrono.submit_gpu = static_cast<double>(stats.gpuTimeEnd - stats.gpuTimeBegin) * _chrono.gpu_ms;
		_chrono.max_gpu_latency = stats.maxGpuLatency;
		_chrono.samples[_chrono.needle] = _chrono.frame_time;
		_chrono.needle = (_chrono.needle + 1) % Chrono::SAMPLE_COUNT;
		_chrono.min_frame_time = std::numeric_limits<double>::min();
		_chrono.max_frame_time = std::numeric_limits<double>::max();
		_chrono.avg_frame_time = .0;
		for (const auto x : _chrono.samples)
		{
			_chrono.min_frame_time = std::min(_chrono.min_frame_time, x);
			_chrono.max_frame_time = std::max(_chrono.max_frame_time, x);
			_chrono.avg_frame_time += x;
		}
		_chrono.avg_frame_time /= Chrono::SAMPLE_COUNT;
		_chrono.fps = 1000. / _chrono.avg_frame_time;
		++_chrono.cycles;

		return now;
	}
}
