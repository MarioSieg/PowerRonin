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
