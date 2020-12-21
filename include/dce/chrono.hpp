#pragma once

#include <cstdint>
#include <chrono>
#include <array>
#include <vector>

namespace dce {
	/// <summary>
	/// Contains time info about an kernel subsystem.
	/// </summary>
	struct SubsystemTimeInfo final {
		double pre_startup = .0;
		double post_startup = .0;
		double pre_tick = .0;
		double post_tick = .0;
	};

	/// <summary>
	/// Contains time info and clocks.
	/// </summary>
	class Chrono final {
	public:
		/// <summary>
		/// Number of time samples to take.
		/// </summary>
		static constexpr auto SAMPLE_COUNT = 256;

		/// <summary>
		/// Cycles since engine start.
		/// </summary>
		std::uint32_t cycles = 0;


		/// <summary>
		/// Engine start time point.
		/// </summary>
		std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now();

		/// <summary>
		/// Max gpu latency.
		/// </summary>
		std::uint32_t max_gpu_latency = 0;

		/// <summary>
		/// Time in seconds since engine start.
		/// </summary>
		double time = .0;

		/// <summary>
		/// Time since last frame between 0 and 1.
		/// </summary>
		double delta_time = .0;

		/// <summary>
		/// Performance frequency.
		/// </summary>
		double frequency = .0;

		/// <summary>
		/// CPU time.
		/// </summary>
		double cpu_ms = .0;

		/// <summary>
		/// GPU time.
		/// </summary>
		double gpu_ms = .0;

		/// <summary>
		/// CPU submit time.
		/// </summary>
		double submit_cpu = .0;

		/// <summary>
		/// GPU submit time.
		/// </summary>
		double submit_gpu = .0;

		/// <summary>
		/// Time the last frame needed in ms.
		/// </summary>
		double frame_time = .0;

		/// <summary>
		/// Average frame time in the last samples.
		/// </summary>
		double avg_frame_time = .0;

		/// <summary>
		/// Min frame time in the last samples.
		/// </summary>
		double min_frame_time = .0;

		/// <summary>
		/// Max frame time in the last samples.
		/// </summary>
		double max_frame_time = .0;

		/// <summary>
		/// Frames per second.
		/// </summary>
		double fps = .0;

		/// <summary>
		/// Time samples.
		/// </summary>
		std::array<double, SAMPLE_COUNT> samples = {};

		/// <summary>
		/// Sample read needle.
		/// </summary>
		std::size_t needle = 0;

		/// <summary>
		/// Kernel subsystem timings.
		/// </summary>
		std::vector<SubsystemTimeInfo> subsystem_timings = {};
	};
}
