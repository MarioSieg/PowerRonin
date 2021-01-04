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

#include "../../include/power_ronin/transform.hpp"

namespace power_ronin
{
	auto Transform::calculate_matrix() const noexcept -> SimdMatrix4x4<>
	{
		auto transform = math::identity<SimdMatrix4x4<>>();
		transform = math::scale(transform, this->scale);
		transform *= mat4_cast(this->rotation);
		transform = translate(transform, this->position);
		return transform;
	}


	auto Transform::forward() const noexcept -> SimdVector3<>
	{
		return this->rotation * SimdVector3<>{0, 0, 1};
	}

	auto Transform::back() const noexcept -> SimdVector3<>
	{
		return this->rotation * SimdVector3<>{0, 0, -1};
	}

	auto Transform::up() const noexcept -> SimdVector3<>
	{
		return this->rotation * SimdVector3<>{0, 1, 0};
	}

	auto Transform::down() const noexcept -> SimdVector3<>
	{
		return this->rotation * SimdVector3<>{0, -1, 0};
	}

	auto Transform::left() const noexcept -> SimdVector3<>
	{
		return this->rotation * SimdVector3<>{-1, 0, 0};
	}

	auto Transform::right() const noexcept -> SimdVector3<>
	{
		return this->rotation * SimdVector3<>{1, 0, 0};
	}
}
