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

#pragma once

#include <cstdint>
#include <chrono>
#include <array>

namespace PowerRonin
{
	/// <summary>
	/// Contains time info about an kernel subsystem.
	/// </summary>
	struct SubsystemTimeInfo final
	{
		double PreStartup = .0;
		double PostStartup = .0;
		double PreTick = .0;
		double PostTick = .0;
	};

	/// <summary>
	/// Contains time info and clocks.
	/// </summary>
	class Chrono final
	{
	public:
		/// <summary>
		/// Number of time samples to take.
		/// </summary>
		static constexpr std::size_t SampleCount = 256;

		/// <summary>
		/// Cycles since engine start.
		/// </summary>
		std::uint32_t Cycles = 0;


		/// <summary>
		/// Engine start time point.
		/// </summary>
		std::chrono::system_clock::time_point StartTime = std::chrono::system_clock::now();

		/// <summary>
		/// Max gpu latency.
		/// </summary>
		std::uint32_t MaxGpuLatency = 0;

		/// <summary>
		/// Time in seconds since engine start.
		/// </summary>
		double Time = .0;

		/// <summary>
		/// Time since last frame between 0 and 1.
		/// </summary>
		double DeltaTime = .0;

		/// <summary>
		/// Performance frequency.
		/// </summary>
		double Frequency = .0;

		/// <summary>
		/// CPU time.
		/// </summary>
		double CpuMs = .0;

		/// <summary>
		/// GPU time.
		/// </summary>
		double GpuMs = .0;

		/// <summary>
		/// CPU submit time.
		/// </summary>
		double SubmitCpu = .0;

		/// <summary>
		/// GPU submit time.
		/// </summary>
		double SubmitGpu = .0;

		/// <summary>
		/// Time the last frame needed in ms.
		/// </summary>
		double FrameTime = .0;

		/// <summary>
		/// Average frame time in the last samples.
		/// </summary>
		double AvgFrameTime = .0;

		/// <summary>
		/// Min frame time in the last samples.
		/// </summary>
		double MinFrameTime = .0;

		/// <summary>
		/// Max frame time in the last samples.
		/// </summary>
		double MaxFrameTime = .0;

		/// <summary>
		/// Frames per second.
		/// </summary>
		double Fps = .0;

		/// <summary>
		/// Time samples.
		/// </summary>
		std::array<double, SampleCount> Samples = {};

		/// <summary>
		/// Sample read needle.
		/// </summary>
		std::size_t Needle = 0;
	};
}
