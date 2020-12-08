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

#include "../../include/dce/audio_clip.hpp"
#include "../include/dce/blob.hpp"
#include "../include/dce/time_utils.hpp"
#include "audio/audio_headers.hpp"


namespace dce {
	namespace audio {
		extern FMOD::System* AUDIO_SYSTEM_HANDLE;
	}

	void AudioClip::upload() { }

	void AudioClip::offload() { }

	auto AudioClipImporteur::load(std::filesystem::path&& _path
	                              , const AudioClipMeta* const _meta) const -> std::shared_ptr<AudioClip> {
		auto self = IResource<AudioClipMeta>::allocate<AudioClip>();
		self->file_path_ = std::move(_path);
		self->meta_data_ = _meta ? *_meta : IResource<AudioClipMeta>::load_meta_or_default(self->file_path_);

		[[unlikely]] if (!audio::AUDIO_SYSTEM_HANDLE) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload audio clip!");
		}

		FMOD_MODE mode = FMOD_DEFAULT;
		mode |= self->meta_data_.enable_3d_sound ? FMOD_3D : FMOD_2D;
		mode |= self->meta_data_.is_stream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

		FMOD::Sound* sound;
		const FMOD_RESULT result = audio::AUDIO_SYSTEM_HANDLE->
			createSound(self->file_path_.string().c_str(), mode, nullptr, &sound);

		[[unlikely]] if (result != FMOD_OK) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload audio clip!");
		}

		self->handle_ = sound;

		return self;
	}
}
