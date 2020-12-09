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

#pragma once

#include "shaders/unlit.hpp"
#include "shaders/lambert.hpp"
#include "shaders/skybox.hpp"

namespace dce::renderer {
	enum class ShaderType {
		UNLIT
		, LAMBERT
	};

	class ShaderBucket final {
	public:
		explicit ShaderBucket(GPU& _gpu) noexcept;
		ShaderBucket(const ShaderBucket&) = delete;
		ShaderBucket(ShaderBucket&&) = delete;
		auto operator=(const ShaderBucket&) = delete;
		auto operator=(ShaderBucket&&) = delete;
		~ShaderBucket() = default;

		void load_all();
		void unload_all();

		shaders::Unlit unlit;
		shaders::Lambert lambert;
		shaders::Skybox skybox;

	private:
		GPU& gpu_;
	};
}
