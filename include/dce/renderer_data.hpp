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

#include "mathlib.hpp"

namespace dce {
	/// <summary>
	/// Contains states and data for the renderer.
	/// </summary>
	class RenderData final {
	public:
		Vector2<> scenery_viewport_size = {.0f, .0f};
		Vector2<> scenery_viewport_position = {.0f, .0f};
		Matrix4x4<> view_matrix = {};
		Matrix4x4<> projection_matrix = {};
		bool enable_wireframe = false;
	};
}
