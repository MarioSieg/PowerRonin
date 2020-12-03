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

#include "audio_clip.hpp"

namespace dce {
	/// <summary>
	/// An audio source component.
	/// </summary>
	class AudioSource final {
	public:
		AudioSource();
		AudioSource(const AudioSource&) = delete;
		AudioSource(AudioSource&&) noexcept;
		auto operator=(const AudioSource&) -> AudioSource& = delete;
		auto operator=(AudioSource&&) noexcept -> AudioSource&;
		~AudioSource();

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
	};
}
