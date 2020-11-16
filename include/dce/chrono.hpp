// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: chrono.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

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
