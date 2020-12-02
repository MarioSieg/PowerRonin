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

#include "../../include/dce/core/kernel.hpp"
#include "audio_headers.hpp"

namespace dce::audio {
	class Audio final : public core::ISubsystem {
	public:
		Audio();
		Audio(const Audio&) = delete;
		Audio(Audio&&) = delete;
		auto operator=(const Audio&) -> Audio& = delete;
		auto operator=(Audio&&) -> Audio& = delete;
		~Audio() override = default;

	private:
		static constexpr auto EVENTS = core::ServiceEvents::PRE_STARTUP | core::ServiceEvents::PRE_TICK | core::ServiceEvents::PRE_SHUTDOWN;

		virtual auto on_pre_startup([[maybe_unused]] Runtime& _rt) -> bool override;
		virtual auto on_pre_tick([[maybe_unused]] Runtime& _rt) -> bool override;
		virtual auto on_pre_shutdown([[maybe_unused]] Runtime& _rt) -> bool override;

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
