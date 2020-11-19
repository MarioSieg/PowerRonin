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
	class Transform final {
	public:
		Vector3<> position = {.0f, .0f, .0f};
		Quaternion<> rotation = {.0f, .0f, .0f, .0f};
		Vector3<> scale = {1.f, 1.f, 1.f};

		[[nodiscard]] auto calculate_matrix() const noexcept -> Matrix4x4<>;
		[[nodiscard]] auto forward() const noexcept -> Vector3<>;
		[[nodiscard]] auto back() const noexcept -> Vector3<>;
		[[nodiscard]] auto up() const noexcept -> Vector3<>;
		[[nodiscard]] auto down() const noexcept -> Vector3<>;
		[[nodiscard]] auto left() const noexcept -> Vector3<>;
		[[nodiscard]] auto right() const noexcept -> Vector3<>;
	};
}
