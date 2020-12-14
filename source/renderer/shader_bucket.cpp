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

#include "shader_bucket.hpp"

namespace dce::renderer {
	ShaderBucket::ShaderBucket(GPU& _gpu) noexcept : unlit(_gpu), lambert(_gpu), skybox(_gpu), gpu_(_gpu) { }

	void ShaderBucket::load_all() {
		this->unlit.load();
		this->lambert.load();
		this->skybox.load();
	}

	void ShaderBucket::unload_all() {
		this->skybox.unload();
		this->lambert.unload();
		this->unlit.unload();
	}
}
