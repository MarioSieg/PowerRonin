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

#include "../include/power_ronin/camera.hpp"

namespace PowerRonin
{
	void Camera::Recalculate(const Transform& transform, const Vector2<>& viewportSize, Matrix4x4<>& outView, Matrix4x4<>& outProj) noexcept
	{
		const Vector3<> up = {.0f, 1.f, .0f};
		outView = Math::lookAtLH(transform.position, transform.position + transform.forward(), up);
		outProj = Math::perspectiveFovLH
		(
			Math::radians(this->Fov),
			static_cast<float>(viewportSize.x),
			static_cast<float>(viewportSize.y),
			this->NearClip,
			this->FarClip
		);
	}
}
