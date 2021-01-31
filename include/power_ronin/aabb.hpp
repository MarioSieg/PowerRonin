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

#pragma once

#include "mathtypes.hpp"
#include <vector>

namespace PowerRonin
{
	/// <summary>
	/// Represents an axis aligned bounding box.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	struct Aabb final
	{
		constexpr Aabb() noexcept = default;
		Aabb(const Vector3<>& min, const Vector3<>& max) noexcept;
		explicit Aabb(const std::vector<Vector3<>>& points) noexcept;
		explicit Aabb(const Vector3<>* const points, const std::size_t count) noexcept;
		constexpr Aabb(const Aabb&) noexcept = default;
		constexpr Aabb(Aabb&&) noexcept = default;
		constexpr auto operator=(const Aabb&) noexcept -> Aabb& = default;
		constexpr auto operator=(Aabb&&) noexcept -> Aabb& = default;
		~Aabb() = default;

		Vector3<> Min = {};
		Vector3<> Max = {};

		[[nodiscard]]
		auto Width() const noexcept -> float;

		[[nodiscard]]
		auto Height() const noexcept -> float;

		[[nodiscard]]
		auto Depth() const noexcept -> float;

		[[nodiscard]]
		auto Size() const noexcept -> Vector3<>;

		[[nodiscard]]
		auto Center() const noexcept -> Vector3<>;

		void Corners(Vector3<> (&out)[8]) const noexcept;
	};
}
