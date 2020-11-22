// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: mathlib.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#define GLM_FORCE_INLINE
#define GLM_FORCE_INTRINSICS
#define GLM_FORCE_SWIZZLE
#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_SIZE_T_LENGTH
//#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "../../extern/glm/glm/geometric.hpp"
#include "../../extern/glm/glm/glm.hpp"
#include "../../extern/glm/glm/matrix.hpp"
#include "../../extern/glm/glm/ext/matrix_clip_space.hpp"
#include "../../extern/glm/glm/ext/matrix_common.hpp"
#include "../../extern/glm/glm/ext/matrix_transform.hpp"
#include "../../extern/glm/glm/gtc/type_ptr.hpp"
#include "../../extern/glm/glm/gtx/transform.hpp"
#include "../../extern/glm/glm/gtx/matrix_decompose.hpp"

namespace dce {
	namespace math = glm;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T> using Vector2 = math::vec<
		2, T, math::defaultp>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T> using Vector3 = math::vec<
		3, T, math::defaultp>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T> using Vector4 = math::vec<
		4, T, math::defaultp>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T> using Quaternion = math::qua<
		T, math::defaultp>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T> using Matrix3x3 = math::mat<
		3, 3, T, math::defaultp>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T> using Matrix4x4 = math::mat<
		4, 4, T, math::defaultp>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T> using Color = Vector4<T>;

	inline auto rgba_to_rgba_norm(const std::uint32_t _rgba) noexcept -> Color<> {
		return Color<>{
			(_rgba >> 24 & 0xFF) / 255.f, (_rgba >> 16 & 0xFF) / 255.f, (_rgba >> 8 & 0xFF) / 255.f, (_rgba & 0xFF) / 255.f
		};
	}
} // namespace dce
