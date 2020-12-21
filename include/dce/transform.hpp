#pragma once

#include "mathlib.hpp"

namespace dce {
	class Transform final {
	public:
		Transform() noexcept = default;
		Transform(const Transform&) noexcept = delete;
		Transform(Transform&&) noexcept = default;
		auto operator=(const Transform&) noexcept -> Transform& = delete;
		auto operator=(Transform&&) noexcept -> Transform& = default;
		~Transform() = default;

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
