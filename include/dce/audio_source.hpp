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
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

#include "audio_clip.hpp"

namespace dce {
	/// <summary>
	/// An audio source component.
	/// </summary>
	class AudioSource final {
	public:
		AudioSource() = default;
		AudioSource(const AudioSource&) = delete;
		AudioSource(AudioSource&&) noexcept = default;
		auto operator=(const AudioSource&) -> AudioSource& = delete;
		auto operator=(AudioSource&&) noexcept -> AudioSource& = default;
		~AudioSource() = default;

		/// <summary>
		/// The audio clip which will be played.
		/// </summary>
		RRef<AudioClip> clip = {};

		/// <summary>
		/// Plays the audio clip.
		/// </summary>
		void play();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>True if the audio source is currently playing, else false.</returns>
		[[nodiscard]] auto is_currently_playing() const noexcept -> bool;


		/// <summary>
		/// Stops current playback.
		/// </summary>
		void stop() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns> The priority for the sound, from 0 (most important) to 256 (least important).</returns>
		[[nodiscard]] auto get_priority() const noexcept -> std::uint8_t;

		/// <summary>
		///  Sets the priority for the sound, from 0 (most important) to 256 (least important).
		/// </summary>
		/// <param name="_priority">The new priority.</param>
		/// <returns></returns>
		void set_priority(const std::uint8_t _priority) const noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="_count"></param>
		/// <returns></returns>
		void set_loop_count(const std::uint32_t _count) const noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		auto get_loop_count() const noexcept -> std::uint32_t;

	private:
		void* channel_ = nullptr;
	};
}
