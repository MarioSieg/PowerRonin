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

#include "mesh.hpp"
#include "shader.hpp"
#include "material.hpp"

namespace dce {
	/// <summary>
	/// A mesh renderer component.
	/// </summary>
	class MeshRenderer final {
	public:
		MeshRenderer() noexcept = default;
		MeshRenderer(const MeshRenderer&) noexcept = delete;
		MeshRenderer(MeshRenderer&&) noexcept = default;
		auto operator=(const MeshRenderer&) noexcept -> MeshRenderer& = delete;
		auto operator=(MeshRenderer&&) noexcept -> MeshRenderer& = default;
		~MeshRenderer() = default;

		RRef<Mesh> mesh = {};
		RRef<Material> material = {};
		bool is_visible = true;
	};
}
