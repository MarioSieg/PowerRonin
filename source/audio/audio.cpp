#include "audio.hpp"

namespace PowerRonin::Audio
{
	AudioSystem::AudioSystem() : ISubsystem("Audio", EVENTS) { }

	void AudioSystem::OnPreStartup(Runtime& runtime)
	{
		auto& proto = runtime.Protocol();

		// Create memory manager:

		AK::MemoryMgr::GetDefaultSettings(this->mem_settings_);
		proto.Info("Initializing audio memory manager...");
		if (AK::MemoryMgr::Init(&this->mem_settings_) != AKRESULT::AK_Success) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to initialize audio memory manager!");
		}

		// Create streaming manager:

		AK::StreamMgr::GetDefaultSettings(this->stream_settings_);
		proto.Info("Initializing audio streaming manager...");
		if (!AK::StreamMgr::Create(this->stream_settings_)) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to initialize audio streaming manager!");
		}

		// Create a streaming device with blocking low-level I/O handshaking:

		AK::StreamMgr::GetDefaultDeviceSettings(this->device_settings_);
		proto.Info("Initializing audio device...");
		if (this->io_.Init(this->device_settings_) != AKRESULT::AK_Success) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to initialize audio device!");
		}

		// Create sound engine:

		AK::SoundEngine::GetDefaultInitSettings(this->init_settings_);
		AK::SoundEngine::GetDefaultPlatformInitSettings(this->platform_init_settings_);
		proto.Info("Initializing sound engine...");
		if (AK::SoundEngine::Init(&this->init_settings_, &this->platform_init_settings_) !=
			AKRESULT::AK_Success) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to initialize sound engine!");
		}

		// Create interactive music engine:

		AK::MusicEngine::GetDefaultInitSettings(this->music_settings_);
		proto.Info("Initializing music engine...");
		if (AK::MusicEngine::Init(&this->music_settings_) != AKRESULT::AK_Success) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to initialize music engine!");
		}

		// Create spatial audio engine:
		proto.Info("Initializing spatial audio...");
		if (AK::SpatialAudio::Init(this->spatial_audio_init_settings_) != AKRESULT::AK_Success) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to initialize spatial audio!");
		}
	}

	void AudioSystem::OnPreTick(Runtime& runtime)
	{
		if (AK::SoundEngine::RenderAudio() != AKRESULT::AK_Success) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Audio rendering failed!");
		}
	}

	void AudioSystem::OnPreShutdown(Runtime&)
	{
		AK::MusicEngine::Term();
		AK::SoundEngine::Term();
		if (AK::IAkStreamMgr::Get()) [[likely]]
		{
			AK::IAkStreamMgr::Get()->Destroy();
		}
		AK::MemoryMgr::Term();
	}
}
