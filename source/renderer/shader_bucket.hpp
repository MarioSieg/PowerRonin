// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#pragma once

#include "shaders/unlit_textured.hpp"
#include "shaders/diffuse.hpp"
#include "shaders/bumped_diffuse.hpp"
#include "shaders/skybox.hpp"

namespace PowerRonin::Renderer
{
	class ShaderBucket final
	{
	public:
		explicit ShaderBucket(GPU& _gpu) noexcept;
		ShaderBucket(const ShaderBucket&) = delete;
		ShaderBucket(ShaderBucket&&) = delete;
		auto operator=(const ShaderBucket&) = delete;
		auto operator=(ShaderBucket&&) = delete;
		~ShaderBucket() = default;

		void load_all();
		void unload_all();

		Shaders::UnlitTexturedShader unlit_textured;
		Shaders::DiffuseShader diffuse;
		Shaders::BumpedDiffuseShader bumped_diffuse;
		Shaders::SkyboxShader skybox;

	private:
		GPU& gpu_;
	};
}
