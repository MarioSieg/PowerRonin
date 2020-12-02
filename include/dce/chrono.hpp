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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

#include <cstdint>
#include <chrono>

namespace dce {
	/* Contains time info and clocks. */
	class Chrono final {
	public:
		std::uint_fast32_t cycles = 0;
		std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now();
		double time = .0;
		double delta_time = .0;
		double frequency = .0;
		double cpu_ms = .0;
		double gpu_ms = .0;
		double frame_ms = .0;
		double submit_cpu = .0;
		double submit_gpu = .0;
		std::uint32_t max_latency = 0;
	};
}
