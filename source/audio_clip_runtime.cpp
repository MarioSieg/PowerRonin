#include "../../include/dce/audio_clip.hpp"
#include "../include/dce/blob.hpp"
#include "audio/audio_headers.hpp"


namespace dce {
	namespace audio {
		extern FMOD::System* AUDIO_SYSTEM_HANDLE;
	}

	void AudioClip::upload() {
	}

	void AudioClip::offload() {
	}

	auto AudioClipImporteur::load(std::filesystem::path&& _path
	                              , const AudioClipMeta* const _meta) const -> std::shared_ptr<AudioClip> {
		auto self = IResource<AudioClipMeta>::allocate<AudioClip>();
		self->file_path_ = std::move(_path);
		self->meta_data_ = _meta ? *_meta : IResource<AudioClipMeta>::load_meta_or_default(self->file_path_);

		[[unlikely]] if (!audio::AUDIO_SYSTEM_HANDLE) {
			throw MAKE_FATAL_ENGINE_EXCEPTION("Failed to upload audio clip!");
		}

		FMOD_MODE mode = FMOD_DEFAULT | FMOD_LOOP_NORMAL;
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
