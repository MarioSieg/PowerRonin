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

#include "../../include/power_ronin/core/kernel.hpp"
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

		void OnPreStartup(Runtime&) override;
		void OnPreTick(Runtime&) override;
		void OnPreShutdown(Runtime&) override;

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
