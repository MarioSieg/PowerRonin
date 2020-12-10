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

#include "../../include/dce/audio_source.hpp"
#include "audio/audio_headers.hpp"

namespace dce {
	namespace audio {
		extern FMOD::System* AUDIO_SYSTEM_HANDLE;
	}

	void AudioSource::play() {
		[[unlikely]] if (!audio::AUDIO_SYSTEM_HANDLE || !this->clip) {
			return;
		}

		auto* sound = static_cast<FMOD::Sound* const>(this->clip->get_handle());
		FMOD::Channel* channel;
		FMOD_RESULT result = audio::AUDIO_SYSTEM_HANDLE->playSound(sound, nullptr, false, &channel);
		[[unlikely]] if (result != FMOD_OK) {
			return;
		}

		result = channel->setPriority(128);
		[[unlikely]] if (result != FMOD_OK) {
			return;
		}

		this->channel_ = channel;
	}

	auto AudioSource::is_currently_playing() const noexcept -> bool {
		bool is_playing;
		return this->channel_ && static_cast<FMOD::Channel*>(this->channel_)->isPlaying(&is_playing) == FMOD_OK && is_playing;
	}

	void AudioSource::stop() const {
		this->channel_ && static_cast<FMOD::Channel*>(this->channel_)->stop() == FMOD_OK;
	}

	auto AudioSource::get_priority() const noexcept -> std::uint8_t {
		[[likely]] if (this->channel_) {
			int prio;
			static_cast<FMOD::Channel*>(this->channel_)->getPriority(&prio);
			return prio;
		}
		return 0;
	}

	void AudioSource::set_priority(const std::uint8_t _priority) const noexcept {
		this->channel_ && static_cast<FMOD::Channel*>(this->channel_)->setPriority(_priority);
	}

	void AudioSource::set_loop_count(const std::uint32_t _count) const noexcept {
		this->channel_ && static_cast<FMOD::Channel*>(this->channel_)->setLoopCount(_count);
	}

	auto AudioSource::get_loop_count() const noexcept -> std::uint32_t {
		[[likely]] if (this->channel_) {
			int count;
			static_cast<FMOD::Channel*>(this->channel_)->getLoopCount(&count);
			return count;
		}
		return 0;
	}

}
