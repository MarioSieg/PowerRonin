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

#include "audio.hpp"
#include "audio_headers.hpp"

namespace dce::audio {
	Audio::Audio() : ISubsystem("Audio", EVENTS) {}

	auto Audio::on_pre_startup(Runtime& _rt) -> bool {

		auto& proto = _rt.protocol();

		// Create memory manager:

		AK::MemoryMgr::GetDefaultSettings(this->mem_settings_);
		proto.critical("Initializing audio memory manager...");
		[[unlikely]] if (AK::MemoryMgr::Init(&this->mem_settings_) != AKRESULT::AK_Success) {
			return false;
		}

		// Create streaming manager:

		AK::StreamMgr::GetDefaultSettings(this->stream_settings_);
		proto.critical("Initializing audio streaming manager...");
		[[unlikely]] if (!AK::StreamMgr::Create(this->stream_settings_)) {
			return false;
		}

		// Create a streaming device with blocking low-level I/O handshaking:

		AK::StreamMgr::GetDefaultDeviceSettings(this->device_settings_);
		proto.critical("Initializing audio device...");
		[[unlikely]] if (this->io_.Init(this->device_settings_) != AKRESULT::AK_Success) {
			return false;
		}

		// Create sound engine:

		AK::SoundEngine::GetDefaultInitSettings(this->init_settings_);
		AK::SoundEngine::GetDefaultPlatformInitSettings(this->platform_init_settings_);
		proto.critical("Initializing sound engine...");
		[[unlikely]] if (AK::SoundEngine::Init(&this->init_settings_, &this->platform_init_settings_) != AKRESULT::AK_Success) {
			return false;
		}

		// Create interactive music engine:

		AK::MusicEngine::GetDefaultInitSettings(this->music_settings_);
		proto.critical("Initializing music engine...");
		[[unlikely]] if (AK::MusicEngine::Init(&this->music_settings_) != AKRESULT::AK_Success) {
			return false;
		}

		// Create spatial audio engine:
		proto.critical("Initializing spatial audio...");
		[[unlikely]] if (AK::SpatialAudio::Init(this->spatial_audio_init_settings_) != AKRESULT::AK_Success) {
			return false;
		}

		return true;
	}

	auto Audio::on_pre_tick(Runtime& _rt) -> bool {
		return AK::SoundEngine::RenderAudio() == AKRESULT::AK_Success;
	}

	auto Audio::on_pre_shutdown(Runtime& _rt) -> bool {
		AK::MusicEngine::Term();
		AK::SoundEngine::Term();
		[[likely]] if (AK::IAkStreamMgr::Get()) {
			AK::IAkStreamMgr::Get()->Destroy();
		}
		AK::MemoryMgr::Term();
		return true;
	}

}
