// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: transform.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "../../include/dce/transform.hpp"

namespace dce {
	auto CTransform::calculate_matrix() const noexcept -> Matrix4x4 {
		auto transform = math::identity<Matrix4x4>();
		transform = math::scale(transform, this->scale);
		transform *= mat4_cast(this->rotation);
		transform = translate(transform, this->position);
		return transform;
	}
}
