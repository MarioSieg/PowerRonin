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

#include "mathlib.hpp"
#include "frustum.hpp"
#include "flycam.hpp"

namespace power_ronin
{
	/// <summary>
	/// Contains states and data for the renderer.
	/// </summary>
	class RenderData final
	{
	public:
		SimdVector2<> scenery_viewport_size = {.0f, .0f};
		SimdVector2<> scenery_viewport_position = {.0f, .0f};
		SimdMatrix4x4<> view_matrix = {};
		SimdMatrix4x4<> projection_matrix = {};
		SimdMatrix4x4<> view_projection_matrix = {};
		Frustum camera_frustum = {};
		SimdMatrix4x4<> skybox_view_matrix = {};
		EditorCamera editor_camera = {};
		bool enable_wireframe = false;
	};
}
