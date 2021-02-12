#pragma once

#include "Frustum.hpp"
#include "EditorCamera.hpp"

namespace PowerRonin
{
	/// <summary>
	/// Contains states and data for the renderer.
	/// </summary>
	class RenderState final
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
