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

#include "gl_headers.hpp"

namespace power_ronin::renderer
{
	/// <summary>
	/// Fullscreen view for effects and clearing.
	/// </summary>
	constexpr bgfx::ViewId FULLSCREEN_VIEW = 0;

	/// <summary>
	/// View to draw the main scenery.
	/// </summary>
	constexpr bgfx::ViewId SCENERY_VIEW = 1;

	/// <summary>
	/// View for the 3D skybox and background stuff.
	/// </summary>
	constexpr bgfx::ViewId SKYBOX_VIEW = 2;

	/// <summary>
	/// View for GUI.
	/// </summary>
	constexpr bgfx::ViewId GUI_VIEW = 0xFF;
}
