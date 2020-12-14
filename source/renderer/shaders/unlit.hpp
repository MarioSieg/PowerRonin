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

#include "../ishader.hpp"

namespace dce::renderer::shaders {
	class Unlit final : public IShader {
	public:
		explicit Unlit(GPU& _gpu) noexcept;

		virtual void load() override;
		virtual void unload() override;

		void per_object(const Mesh& _mesh, const Material::Unlit& _mat) const;

	private:
		bgfx::UniformHandle u_s_tex_color_ = {bgfx::kInvalidHandle};
	};
}
