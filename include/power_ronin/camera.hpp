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

namespace power_ronin
{
	/// <summary>
	/// A Camera component.
	/// </summary>
	class Camera final
	{
	public:
		float fov_y = 80.F;
		float near_clip_z = 0.01F;
		float far_clip_z = 1000.F;

		[[nodiscard]] auto view_matrix() const noexcept -> const SMat4x4<>&;
		[[nodiscard]] auto projection_matrix() const noexcept -> const SMat4x4<>&;
		void recalculate(const Transform& _transform, const RenderData& _data) noexcept;

	private:
		SMat4x4<> view_ = {};
		SMat4x4<> projection_ = {};
	};
}
