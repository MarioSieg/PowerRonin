// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: transform.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "mathlib.hpp"

namespace dce {
	class CTransform final {
	public:
		Vec3 position = {.0f, .0f, .0f};
		Quaternion rotation = {.0f, .0f, .0f, .0f};
		Vec3 scale = {1.f, 1.f, 1.f};

		[[nodiscard]] auto calculate_matrix() const noexcept -> Matrix4x4;
	};
}
