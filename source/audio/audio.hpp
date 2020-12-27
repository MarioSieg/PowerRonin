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
		static constexpr auto EVENTS = core::ServiceEvents::PRE_STARTUP | core::ServiceEvents::PRE_TICK |
			core::ServiceEvents::PRE_SHUTDOWN;

		auto on_pre_startup([[maybe_unused]] Runtime& _rt) -> bool override;
		auto on_pre_tick([[maybe_unused]] Runtime& _rt) -> bool override;
		auto on_pre_shutdown([[maybe_unused]] Runtime& _rt) -> bool override;

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
