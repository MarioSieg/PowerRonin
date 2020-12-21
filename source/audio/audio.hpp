#pragma once

#include "../../include/dce/core/kernel.hpp"
#include "audio_headers.hpp"

namespace dce::audio {
	extern FMOD::System* AUDIO_SYSTEM_HANDLE;

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

		FMOD::System* system_ = nullptr;
	};
}
