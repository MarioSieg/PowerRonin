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

#pragma once

#include "../ishader.hpp"

namespace dce::renderer::shaders {

	class Skybox final : public IShader {
	public:
		explicit Skybox(GPU& _gpu) noexcept;

		virtual void load() override;
		virtual void unload() override;
		void per_frame(const Texture& _skybox, const Mesh& _skydome) const;

	private:
		bgfx::UniformHandle u_s_tex_cube_ = {bgfx::kInvalidHandle};
	};
}
