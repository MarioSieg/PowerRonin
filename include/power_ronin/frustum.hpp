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

#include "aabb.hpp"

namespace power_ronin
{
	/// <summary>
	/// Represents a view frustum (camera pyramid)
	/// </summary>
	struct Frustum final
	{
		enum Planes
		{
			LEFT = 0,
			RIGHT,
			BOTTOM,
			TOP,
			NEAR,
			FAR,
			COUNT,
			COMBO = COUNT * (COUNT - 1) / 2
		};

		constexpr Frustum() noexcept = default;
		constexpr Frustum(const Frustum&) noexcept = default;
		constexpr Frustum(Frustum&&) noexcept = default;
		constexpr auto operator=(const Frustum&) noexcept -> Frustum& = default;
		constexpr auto operator=(Frustum&&) noexcept -> Frustum& = default;
		~Frustum() = default;

		[[nodiscard]]
		auto planes() const noexcept -> const SimdVector4<>(&)[6];

		[[nodiscard]]
		auto points() const noexcept -> const SimdVector3<>(&)[8];

		void from_camera_matrix(const SimdMatrix4x4<>& _view_proj) noexcept;

		[[nodiscard]]
		auto is_aabb_visible(const AABB& _in) const noexcept -> bool;

	private:
		SimdVector4<> planes_[6] = {};
		SimdVector3<> points_[8] = {};
	};
}
