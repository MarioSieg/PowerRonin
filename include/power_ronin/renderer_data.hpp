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

#include "frustum.hpp"
#include "flycam.hpp"

namespace PowerRonin
{
	/// <summary>
	/// Contains states and data for the renderer.
	/// </summary>
	class RenderData final
	{
	public:
		Viewport<> PrimaryViewport = {};
		Matrix4x4<> ViewMatrix = {};
		Matrix4x4<> ProjectionMatrix = {};
		Matrix4x4<> ViewProjectionMatrix = {};
		Frustum CameraFrustum = {};
		Matrix4x4<> SkyboxViewMatrix = {};

#if AUTO_TEC
		EditorCamera EditorCamera = {};
		bool EnableWireframe = false;
#endif
	};
}
