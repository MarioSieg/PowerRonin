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

#include "audio.hpp"

namespace power_ronin::audio
{
	Audio::Audio() : ISubsystem("Audio", EVENTS) { }

	auto Audio::on_pre_startup(Runtime& _rt) -> bool
	{
		auto& proto = _rt.protocol();

		// Create memory manager:

		AK::MemoryMgr::GetDefaultSettings(this->mem_settings_);
		proto.info("Initializing audio memory manager...");
		if (AK::MemoryMgr::Init(&this->mem_settings_) != AKRESULT::AK_Success) [[unlikely]]
		{
			return false;
		}

		// Create streaming manager:

		AK::StreamMgr::GetDefaultSettings(this->stream_settings_);
		proto.info("Initializing audio streaming manager...");
		if (!AK::StreamMgr::Create(this->stream_settings_)) [[unlikely]]
		{
			return false;
		}

		// Create a streaming device with blocking low-level I/O handshaking:

		AK::StreamMgr::GetDefaultDeviceSettings(this->device_settings_);
		proto.info("Initializing audio device...");
		if (this->io_.Init(this->device_settings_) != AKRESULT::AK_Success) [[unlikely]]
		{
			return false;
		}

		// Create sound engine:

		AK::SoundEngine::GetDefaultInitSettings(this->init_settings_);
		AK::SoundEngine::GetDefaultPlatformInitSettings(this->platform_init_settings_);
		proto.info("Initializing sound engine...");
		if (AK::SoundEngine::Init(&this->init_settings_, &this->platform_init_settings_) !=
			AKRESULT::AK_Success) [[unlikely]]
		{
			return false;
		}

		// Create interactive music engine:

		AK::MusicEngine::GetDefaultInitSettings(this->music_settings_);
		proto.info("Initializing music engine...");
		if (AK::MusicEngine::Init(&this->music_settings_) != AKRESULT::AK_Success) [[unlikely]]
		{
			return false;
		}

		// Create spatial audio engine:
		proto.info("Initializing spatial audio...");
		if (AK::SpatialAudio::Init(this->spatial_audio_init_settings_) != AKRESULT::AK_Success) [[unlikely]]
		{
			return false;
		}

		return true;
	}

	auto Audio::on_pre_tick(Runtime& _rt) -> bool
	{
		return AK::SoundEngine::RenderAudio() == AKRESULT::AK_Success;
	}

	auto Audio::on_pre_shutdown(Runtime& _rt) -> bool
	{
		AK::MusicEngine::Term();
		AK::SoundEngine::Term();
		if (AK::IAkStreamMgr::Get()) [[likely]]
		{
			AK::IAkStreamMgr::Get()->Destroy();
		}
		AK::MemoryMgr::Term();
		return true;
	}
}
