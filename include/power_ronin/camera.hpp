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

#include "renderer_data.hpp"
#include "transform.hpp"

namespace PowerRonin
{
	/// <summary>
	/// A Camera component.
	/// </summary>
	class Camera final
	{
	public:
		float Fov = 80.F;
		float NearClip = 0.01F;
		float FarClip = 1000.F;

		void Recalculate(const Transform& transform, const Vector2<>& viewportSize, Matrix4x4<>& outView, Matrix4x4<>& outProj) noexcept;
	};
}
