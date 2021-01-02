#pragma once

#include "mathlib.hpp"

namespace dce
{
	class Transform final
	{
	public:
		Transform() noexcept = default;
		Transform(const Transform&) noexcept = delete;
		Transform(Transform&&) noexcept = default;
		auto operator=(const Transform&) noexcept -> Transform& = delete;
		auto operator=(Transform&&) noexcept -> Transform& = default;
		~Transform() = default;

		SimdVector3<> position = {.0f, .0f, .0f};
		SimdQuaternion<> rotation = {.0f, .0f, .0f, .0f};
		SimdVector3<> scale = {1.f, 1.f, 1.f};

		[[nodiscard]] auto calculate_matrix() const noexcept -> SimdMatrix4x4<>;
		[[nodiscard]] auto forward() const noexcept -> SimdVector3<>;
		[[nodiscard]] auto back() const noexcept -> SimdVector3<>;
		[[nodiscard]] auto up() const noexcept -> SimdVector3<>;
		[[nodiscard]] auto down() const noexcept -> SimdVector3<>;
		[[nodiscard]] auto left() const noexcept -> SimdVector3<>;
		[[nodiscard]] auto right() const noexcept -> SimdVector3<>;
	};
}
