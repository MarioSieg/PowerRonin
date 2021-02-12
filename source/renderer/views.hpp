#pragma once

#include "gl_headers.hpp"

namespace PowerRonin::Renderer
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
