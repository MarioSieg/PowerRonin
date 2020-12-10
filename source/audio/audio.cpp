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

#include "audio.hpp"
#include "audio_headers.hpp"
#include "../wincom.hpp"

namespace dce::audio {
	FMOD::System* AUDIO_SYSTEM_HANDLE = nullptr;

	Audio::Audio() : ISubsystem("Audio", EVENTS) {}

	auto Audio::on_pre_startup(Runtime& _rt) -> bool {

		auto& proto = _rt.protocol();

		proto.info("Initializing COM...");
		co_initialize();

		proto.info("Creating audio system...");

		FMOD_RESULT result = System_Create(&this->system_);
		[[unlikely]] if (result != FMOD_OK) {
			return false;
		}

		const auto max_channels = _rt.config().audio.max_channels;
		constexpr auto flags = FMOD_INIT_NORMAL; //| FMOD_INIT_3D_RIGHTHANDED;
		proto.info("Initializing audio system...");

		result = this->system_->init(max_channels, flags, nullptr);
		[[unlikely]] if (result != FMOD_OK) {
			return false;
		}

		proto.info("Max channels: {}", max_channels);
		proto.info("Creation flags: {:B}", flags);

		AUDIO_SYSTEM_HANDLE = this->system_;

		return true;
	}

	auto Audio::on_pre_tick(Runtime& _rt) -> bool {
		return true;
	}

	auto Audio::on_pre_shutdown(Runtime& _rt) -> bool {
		[[likely]] if (this->system_) {
			this->system_->release();
			this->system_ = nullptr;
			AUDIO_SYSTEM_HANDLE = nullptr;
		}
		co_uninitialize();
		return true;
	}

}
