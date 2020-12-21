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
		[[nodiscard]] auto get_loop_count() const noexcept -> std::uint32_t;

		/// <summary>
		/// Sets the audio source volume (0.0-1.0).
		/// </summary>
		/// <param name="_volume"></param>
		/// <returns></returns>
		void set_volume(const float _volume) const noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The audio source volume.</returns>
		[[nodiscard]] auto get_volume() const noexcept -> float;

	private:
		void* channel_ = nullptr;
	};
}
