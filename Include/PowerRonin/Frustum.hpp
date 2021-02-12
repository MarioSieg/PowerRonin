#pragma once

#include "Aabb.hpp"

namespace PowerRonin
{
	/// <summary>
	/// Represents a view frustum (camera pyramid)
	/// </summary>
	struct Frustum final
	{
		enum Planes
		{
			Left = 0,
			Right,
			Bottom,
			Top,
			Near,
			Far,
			Count,
			Combo = Count * (Count - 1) / 2
		};

		constexpr Frustum() noexcept = default;
		constexpr Frustum(const Frustum&) noexcept = default;
		constexpr Frustum(Frustum&&) noexcept = default;
		constexpr auto operator=(const Frustum&) noexcept -> Frustum& = default;
		constexpr auto operator=(Frustum&&) noexcept -> Frustum& = default;
		~Frustum() = default;

		[[nodiscard]]
		auto Planes() const noexcept -> const Vector4<>(&)[6];

		[[nodiscard]]
		auto Points() const noexcept -> const Vector3<>(&)[8];

		void FromCameraMatrix(const Matrix4x4<>& viewProj) noexcept;

		[[nodiscard]]
		auto IsAabbVisible(const Aabb& in) const noexcept -> bool;

	private:
		Vector4<> planes[6] = {};
		Vector3<> points[8] = {};
	};
}
