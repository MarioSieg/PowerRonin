#pragma once

#include "../../Include/PowerRonin/core/Kernel.hpp"
#include "audio_headers.hpp"

namespace PowerRonin::Audio
{
	class AudioSystem final : public Core::ISubsystem
	{
	public:
		AudioSystem();
		AudioSystem(const AudioSystem&) = delete;
		AudioSystem(AudioSystem&&) = delete;
		auto operator=(const AudioSystem&) -> AudioSystem& = delete;
		auto operator=(AudioSystem&&) -> AudioSystem& = delete;
		~AudioSystem() override = default;

	private:
		static constexpr auto EVENTS = Core::ServiceEvents::PreStartup | Core::ServiceEvents::PreTick |
			Core::ServiceEvents::PreShutdown;

		virtual void OnPreStartup(Runtime&) override;
		virtual void OnPreTick(Runtime&) override;
		virtual void OnPreShutdown(Runtime&) override;

		AkMemSettings mem_settings_ = {};
		AkStreamMgrSettings stream_settings_ = {};
		AkDeviceSettings device_settings_ = {};
		AkInitSettings init_settings_ = {};
		AkPlatformInitSettings platform_init_settings_ = {};
		AkMusicSettings music_settings_ = {};
		AkSpatialAudioInitSettings spatial_audio_init_settings_ = {};
		CAkDefaultIOHookBlocking io_ = {};
	};
}
