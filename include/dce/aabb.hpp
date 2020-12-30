#pragma once

#include "mathtypes.hpp"
#include <vector>

namespace dce {
	/// <summary>
	/// Represents an axis aligned bounding box.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	struct AABB final {
		constexpr AABB() noexcept = default;
		AABB(const SimdVector3<>& _min, const SimdVector3<>& _max) noexcept;
		explicit AABB(const std::vector<SimdVector3<>>& _points) noexcept;
		explicit AABB(const SimdVector3<>* const _points, const std::size_t _count) noexcept;
		constexpr AABB(const AABB&) noexcept = default;
		constexpr AABB(AABB&&) noexcept = default;
		constexpr auto operator=(const AABB&) noexcept -> AABB& = default;
		constexpr auto operator=(AABB&&) noexcept -> AABB& = default;
		~AABB() = default;

		SimdVector3<> min = {};
		SimdVector3<> max = {};

		[[nodiscard]]
		auto width() const noexcept -> float;

		[[nodiscard]]
		auto height() const noexcept -> float;

		[[nodiscard]]
		auto depth() const noexcept -> float;

		[[nodiscard]]
		auto size() const noexcept -> SimdVector3<>;

		[[nodiscard]]
		auto center() const noexcept -> SimdVector3<>;

		void corners(SimdVector3<> (&_out)[8]) const noexcept;
	};
}
