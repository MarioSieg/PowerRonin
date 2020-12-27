#pragma once

#include "aabb.hpp"

namespace dce {
	/// <summary>
	/// Represents a view frustum (camera pyramid)
	/// </summary>
	struct Frustum final {
		enum Planes {
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
