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

namespace power_ronin
{
	auto Camera::view_matrix() const noexcept -> const SMat4x4<>&
	{
		return this->view_;
	}

	auto Camera::projection_matrix() const noexcept -> const SMat4x4<>&
	{
		return this->projection_;
	}

	void Camera::recalculate(const Transform& _transform, const RenderData& _data) noexcept
	{
		const SVec3<> up = {.0f, 1.f, .0f};
		this->view_ = math::lookAtLH(_transform.position, _transform.position + _transform.forward(), up);
		this->projection_ = math::perspectiveFovLH(
			math::radians(this->fov_y),
			static_cast<float>(_data.primary_viewport.z),
			static_cast<float>(_data.primary_viewport.w),
			this->near_clip_z,
			this->far_clip_z
		);
	}
}
