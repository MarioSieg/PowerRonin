#include "../../include/dce/audio_clip.hpp"
#include "../../include/dce/json_impl.hpp"

namespace dce {
	auto AudioClip::get_handle() const noexcept -> void* {
		return this->handle_;
	}

	void AudioClipMeta::serialize(JsonStream& _j) const {
		_j["is_stream"] = this->is_stream;
		_j["enable_3d_sound"] = this->enable_3d_sound;
	}

	void AudioClipMeta::deserialize(const JsonStream& _j) {
		this->is_stream = _j["is_stream"];
		this->enable_3d_sound = _j["enable_3d_sound"];
	}
}
