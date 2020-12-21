#pragma once

#include "mathtypes.hpp"

/* Sadly we cannot use constexpr here because glm is C++ 11. */

namespace dce::math {
	inline const Vector3<> BACK = {0, 0, -1};
	inline const Vector3<> DOWN = {0, -1, 0};
	inline const Vector3<> FORWARD = {0, 0, 1};
	inline const Vector3<> LEFT = {-1, 0, 0};
	inline const Vector3<> RIGHT = {1, 0, 0};
	inline const Vector3<> UP = {0, 1, 0};
	inline const Vector3<> ZERO = {0, 0, 0};
	inline const Vector3<> ONE = {1, 1, 1};
	inline const Vector3<> NORTH = {0, 0, 1};
	inline const Vector3<> SOUTH = {0, 0, -1};
	inline const Vector3<> EAST = {1, 0, 0};
	inline const Vector3<> WEST = {-1, 0, 0};

	inline auto rgba_to_rgba_norm(const std::uint32_t _rgba) noexcept -> Color<> {
		return Color<>{
			(_rgba >> 24 & 0xFF) / 255.f, (_rgba >> 16 & 0xFF) / 255.f, (_rgba >> 8 & 0xFF) / 255.f,
			(_rgba & 0xFF) / 255.f
		};
	}

	template <typename T> requires requires {
		requires std::is_integral_v<T> || std::is_floating_point_v<T>;
	} constexpr auto
	map_range(const T _x, const T _in_min, const T _in_max, const T _out_min, const T _out_max) noexcept -> T {
		return (_x - _in_min) * (_out_max - _out_min) / (_in_max - _in_min) + _out_min;
	}

}
