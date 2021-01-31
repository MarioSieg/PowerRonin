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

namespace PowerRonin::Renderer
{
	auto update_clocks(Chrono& _chrono, const std::uint64_t _prev) noexcept -> std::uint64_t
	{
		const auto& stats = *bgfx::getStats();
		const auto now = get_high_precision_counter();

		_chrono.Frequency = static_cast<double>(get_high_precision_frequency());
		_chrono.DeltaTime = static_cast<double>(get_high_precision_counter() - _prev) / _chrono.Frequency;
		_chrono.Time += _chrono.DeltaTime;
		_chrono.CpuMs = 1000. / static_cast<double>(stats.cpuTimerFreq);
		_chrono.GpuMs = 1000. / static_cast<double>(stats.gpuTimerFreq);
		_chrono.FrameTime = static_cast<double>(stats.cpuTimeFrame) * _chrono.CpuMs;
		_chrono.SubmitCpu = static_cast<double>(stats.cpuTimeEnd - stats.cpuTimeBegin) * _chrono.CpuMs;
		_chrono.SubmitGpu = static_cast<double>(stats.gpuTimeEnd - stats.gpuTimeBegin) * _chrono.GpuMs;
		_chrono.MaxGpuLatency = stats.maxGpuLatency;
		_chrono.Samples[_chrono.Needle] = _chrono.FrameTime;
		_chrono.Needle = (_chrono.Needle + 1) % Chrono::SampleCount;
		_chrono.MinFrameTime = std::numeric_limits<double>::min();
		_chrono.MaxFrameTime = std::numeric_limits<double>::max();
		_chrono.AvgFrameTime = .0;
		for (const auto x : _chrono.Samples)
		{
			_chrono.MinFrameTime = std::min(_chrono.MinFrameTime, x);
			_chrono.MaxFrameTime = std::max(_chrono.MaxFrameTime, x);
			_chrono.AvgFrameTime += x;
		}
		_chrono.AvgFrameTime /= Chrono::SampleCount;
		_chrono.Fps = 1000. / _chrono.AvgFrameTime;
		++_chrono.Cycles;

		return now;
	}
}
