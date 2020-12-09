// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../../include/dce/transform.hpp"

namespace dce {
	auto Transform::calculate_matrix() const noexcept -> Matrix4x4<> {
		auto transform = math::identity<Matrix4x4<>>();
		transform = math::scale(transform, this->scale);
		transform *= mat4_cast(this->rotation);
		transform = translate(transform, this->position);
		return transform;
	}


	auto Transform::forward() const noexcept -> Vector3<> {
		return this->rotation * Vector3<>{0, 0, 1};
	}

	auto Transform::back() const noexcept -> Vector3<> {
		return this->rotation * Vector3<>{0, 0, -1};
	}

	auto Transform::up() const noexcept -> Vector3<> {
		return this->rotation * Vector3<>{0, 1, 0};
	}

	auto Transform::down() const noexcept -> Vector3<> {
		return this->rotation * Vector3<>{0, -1, 0};
	}

	auto Transform::left() const noexcept -> Vector3<> {
		return this->rotation * Vector3<>{-1, 0, 0};
	}

	auto Transform::right() const noexcept -> Vector3<> {
		return this->rotation * Vector3<>{1, 0, 0};
	}
}
