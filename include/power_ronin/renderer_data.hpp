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
		Viewport<> primary_viewport = {};
		SMat4x4<> view_matrix = {};
		SMat4x4<> projection_matrix = {};
		SMat4x4<> view_projection_matrix = {};
		Frustum camera_frustum = {};
		SMat4x4<> skybox_view_matrix = {};

#if AUTO_TEC
		EditorCamera editor_camera = {};
		bool enable_wireframe = false;
#endif
	};
}
