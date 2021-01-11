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

namespace power_ronin
{
	/// <summary>
	/// Represents an axis aligned bounding box.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	struct AABB final
	{
		constexpr AABB() noexcept = default;
		AABB(const SVec3<>& _min, const SVec3<>& _max) noexcept;
		explicit AABB(const std::vector<SVec3<>>& _points) noexcept;
		explicit AABB(const SVec3<>* const _points, const std::size_t _count) noexcept;
		constexpr AABB(const AABB&) noexcept = default;
		constexpr AABB(AABB&&) noexcept = default;
		constexpr auto operator=(const AABB&) noexcept -> AABB& = default;
		constexpr auto operator=(AABB&&) noexcept -> AABB& = default;
		~AABB() = default;

		SVec3<> min = {};
		SVec3<> max = {};

		[[nodiscard]]
		auto width() const noexcept -> float;

		[[nodiscard]]
		auto height() const noexcept -> float;

		[[nodiscard]]
		auto depth() const noexcept -> float;

		[[nodiscard]]
		auto size() const noexcept -> SVec3<>;

		[[nodiscard]]
		auto center() const noexcept -> SVec3<>;

		void corners(SVec3<> (&_out)[8]) const noexcept;
	};
}
