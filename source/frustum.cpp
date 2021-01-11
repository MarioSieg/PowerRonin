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

#include "../include/power_ronin/frustum.hpp"

namespace power_ronin
{
	template <Frustum::Planes I, Frustum::Planes J>
	struct IJ2K
	{
		enum { K = I * (9 - I) / 2 + J - 1 };
	};

	template <Frustum::Planes A, Frustum::Planes B, Frustum::Planes C>
	[[nodiscard]] static auto intersection(const Frustum& _frustum,
	                                       const SVec3<>* const _crosses) noexcept -> SVec3<>
	{
		const auto& planes = _frustum.planes();
		const auto D = math::dot(SVec3<>(planes[A]), _crosses[IJ2K<B, C>::K]);
		SVec3<> res = glm::mat3(_crosses[IJ2K<B, C>::K], -_crosses[IJ2K<A, C>::K], _crosses[IJ2K<A, B>::K])
			* SVec3<>(planes[A].w, planes[B].w, planes[C].w);
		return res * (-1.0f / D);
	}

	auto Frustum::planes() const noexcept -> const SVec4<>(&)[COUNT]
	{
		return this->planes_;
	}

	auto Frustum::points() const noexcept -> const SVec3<>(&)[8]
	{
		return this->points_;
	}

	void Frustum::from_camera_matrix(const SMat4x4<>& _view_proj) noexcept
	{
		auto matrix = math::transpose(_view_proj);
		this->planes_[LEFT] = matrix[3] + matrix[0];
		this->planes_[RIGHT] = matrix[3] - matrix[0];
		this->planes_[BOTTOM] = matrix[3] + matrix[1];
		this->planes_[TOP] = matrix[3] - matrix[1];
		this->planes_[NEAR] = matrix[3] + matrix[2];
		this->planes_[FAR] = matrix[3] - matrix[2];

		SVec3<> crosses[COMBO] = {
			math::cross(SVec3<>(this->planes_[LEFT]), SVec3<>(this->planes_[RIGHT])),
			math::cross(SVec3<>(this->planes_[LEFT]), SVec3<>(this->planes_[BOTTOM])),
			math::cross(SVec3<>(this->planes_[LEFT]), SVec3<>(this->planes_[TOP])),
			math::cross(SVec3<>(this->planes_[LEFT]), SVec3<>(this->planes_[NEAR])),
			math::cross(SVec3<>(this->planes_[LEFT]), SVec3<>(this->planes_[FAR])),
			math::cross(SVec3<>(this->planes_[RIGHT]), SVec3<>(this->planes_[BOTTOM])),
			math::cross(SVec3<>(this->planes_[RIGHT]), SVec3<>(this->planes_[TOP])),
			math::cross(SVec3<>(this->planes_[RIGHT]), SVec3<>(this->planes_[NEAR])),
			math::cross(SVec3<>(this->planes_[RIGHT]), SVec3<>(this->planes_[FAR])),
			math::cross(SVec3<>(this->planes_[BOTTOM]), SVec3<>(this->planes_[TOP])),
			math::cross(SVec3<>(this->planes_[BOTTOM]), SVec3<>(this->planes_[NEAR])),
			math::cross(SVec3<>(this->planes_[BOTTOM]), SVec3<>(this->planes_[FAR])),
			math::cross(SVec3<>(this->planes_[TOP]), SVec3<>(this->planes_[NEAR])),
			math::cross(SVec3<>(this->planes_[TOP]), SVec3<>(this->planes_[FAR])),
			math::cross(SVec3<>(this->planes_[NEAR]), SVec3<>(this->planes_[FAR]))
		};

		this->points_[0] = intersection<LEFT, BOTTOM, NEAR>(*this, crosses);
		this->points_[1] = intersection<LEFT, TOP, NEAR>(*this, crosses);
		this->points_[2] = intersection<RIGHT, BOTTOM, NEAR>(*this, crosses);
		this->points_[3] = intersection<RIGHT, TOP, NEAR>(*this, crosses);
		this->points_[4] = intersection<LEFT, BOTTOM, FAR>(*this, crosses);
		this->points_[5] = intersection<LEFT, TOP, FAR>(*this, crosses);
		this->points_[6] = intersection<RIGHT, BOTTOM, FAR>(*this, crosses);
		this->points_[7] = intersection<RIGHT, TOP, FAR>(*this, crosses);
	}

	auto Frustum::is_aabb_visible(const AABB& _in) const noexcept -> bool
	{
		const auto& minp = _in.min;
		const auto& maxp = _in.max;

		if (math::dot(this->planes_[0], SVec4<>(minp.x, minp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[0], SVec4<>(maxp.x, minp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[0], SVec4<>(minp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[0], SVec4<>(maxp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[0], SVec4<>(minp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[0], SVec4<>(maxp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[0], SVec4<>(minp.x, maxp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[0], SVec4<>(maxp.x, maxp.y, maxp.z, 1.0f)) < .0F) [[likely]]
		{
			return false;
		}

		if (math::dot(this->planes_[1], SVec4<>(minp.x, minp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[1], SVec4<>(maxp.x, minp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[1], SVec4<>(minp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[1], SVec4<>(maxp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[1], SVec4<>(minp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[1], SVec4<>(maxp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[1], SVec4<>(minp.x, maxp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[1], SVec4<>(maxp.x, maxp.y, maxp.z, 1.0f)) < .0F) [[likely]]
		{
			return false;
		}

		if (math::dot(this->planes_[2], SVec4<>(minp.x, minp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[2], SVec4<>(maxp.x, minp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[2], SVec4<>(minp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[2], SVec4<>(maxp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[2], SVec4<>(minp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[2], SVec4<>(maxp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[2], SVec4<>(minp.x, maxp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[2], SVec4<>(maxp.x, maxp.y, maxp.z, 1.0f)) < .0F) [[likely]]
		{
			return false;
		}

		if (math::dot(this->planes_[3], SVec4<>(minp.x, minp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[3], SVec4<>(maxp.x, minp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[3], SVec4<>(minp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[3], SVec4<>(maxp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[3], SVec4<>(minp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[3], SVec4<>(maxp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[3], SVec4<>(minp.x, maxp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[3], SVec4<>(maxp.x, maxp.y, maxp.z, 1.0f)) < .0F) [[likely]]
		{
			return false;
		}

		if (math::dot(this->planes_[4], SVec4<>(minp.x, minp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[4], SVec4<>(maxp.x, minp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[4], SVec4<>(minp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[4], SVec4<>(maxp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[4], SVec4<>(minp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[4], SVec4<>(maxp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[4], SVec4<>(minp.x, maxp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[4], SVec4<>(maxp.x, maxp.y, maxp.z, 1.0f)) < .0F) [[likely]]
		{
			return false;
		}

		if (math::dot(this->planes_[5], SVec4<>(minp.x, minp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[5], SVec4<>(maxp.x, minp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[5], SVec4<>(minp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[5], SVec4<>(maxp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[5], SVec4<>(minp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[5], SVec4<>(maxp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[5], SVec4<>(minp.x, maxp.y, maxp.z, 1.0f)) < .0F &&
			math::dot(this->planes_[5], SVec4<>(maxp.x, maxp.y, maxp.z, 1.0f)) < .0F) [[likely]]
		{
			return false;
		}

		std::int_fast32_t out = 0;

		out += this->points_[0].x > maxp.x;
		out += this->points_[1].x > maxp.x;
		out += this->points_[2].x > maxp.x;
		out += this->points_[3].x > maxp.x;
		out += this->points_[4].x > maxp.x;
		out += this->points_[5].x > maxp.x;
		out += this->points_[6].x > maxp.x;
		out += this->points_[7].x > maxp.x;

		if (out == 8) [[likely]]
		{
			return false;
		}

		out = 0;

		out += this->points_[0].x < minp.x;
		out += this->points_[1].x < minp.x;
		out += this->points_[2].x < minp.x;
		out += this->points_[3].x < minp.x;
		out += this->points_[4].x < minp.x;
		out += this->points_[5].x < minp.x;
		out += this->points_[6].x < minp.x;
		out += this->points_[7].x < minp.x;

		if (out == 8) [[likely]]
		{
			return false;
		}

		out = 0;

		out += this->points_[0].y > maxp.y;
		out += this->points_[1].y > maxp.y;
		out += this->points_[2].y > maxp.y;
		out += this->points_[3].y > maxp.y;
		out += this->points_[4].y > maxp.y;
		out += this->points_[5].y > maxp.y;
		out += this->points_[6].y > maxp.y;
		out += this->points_[7].y > maxp.y;

		if (out == 8) [[likely]]
		{
			return false;
		}

		out = 0;

		out += this->points_[0].y < minp.y;
		out += this->points_[1].y < minp.y;
		out += this->points_[2].y < minp.y;
		out += this->points_[3].y < minp.y;
		out += this->points_[4].y < minp.y;
		out += this->points_[5].y < minp.y;
		out += this->points_[6].y < minp.y;
		out += this->points_[7].y < minp.y;

		if (out == 8) [[likely]]
		{
			return false;
		}

		out = 0;

		out += this->points_[0].z > maxp.z;
		out += this->points_[1].z > maxp.z;
		out += this->points_[2].z > maxp.z;
		out += this->points_[3].z > maxp.z;
		out += this->points_[4].z > maxp.z;
		out += this->points_[5].z > maxp.z;
		out += this->points_[6].z > maxp.z;
		out += this->points_[7].z > maxp.z;

		if (out == 8) [[likely]]
		{
			return false;
		}

		out = 0;

		out += this->points_[0].z < minp.z;
		out += this->points_[1].z < minp.z;
		out += this->points_[2].z < minp.z;
		out += this->points_[3].z < minp.z;
		out += this->points_[4].z < minp.z;
		out += this->points_[5].z < minp.z;
		out += this->points_[6].z < minp.z;
		out += this->points_[7].z < minp.z;

		if (out == 8) [[likely]]
		{
			return false;
		}

		return true;
	}
}
