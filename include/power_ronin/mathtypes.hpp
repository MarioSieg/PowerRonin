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

#define GLM_HAS_CONSTEXPR
#define GLM_FORCE_INLINE
#define GLM_FORCE_INTRINSICS
#define GLM_FORCE_SWIZZLE
#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_SIZE_T_LENGTH
#define GLM_CONSTEXPR_SIMD
#define GLM_FORCE_ALIGNED

#include "../../extern/glm/glm/geometric.hpp"
#include "../../extern/glm/glm/glm.hpp"
#include "../../extern/glm/glm/matrix.hpp"
#include "../../extern/glm/glm/ext/matrix_clip_space.hpp"
#include "../../extern/glm/glm/ext/matrix_common.hpp"
#include "../../extern/glm/glm/ext/matrix_transform.hpp"
#include "../../extern/glm/glm/gtc/type_ptr.hpp"
#include "../../extern/glm/glm/gtx/transform.hpp"
#include "../../extern/glm/glm/gtx/matrix_decompose.hpp"
#include <cstdint>

namespace power_ronin
{
	namespace math
	{
		using namespace glm;
	}

	// @formatter:off

	constexpr auto ALIGNED_PRECISION = math::aligned_highp;
	constexpr auto FIXED_PRECISION = math::mediump;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using SimdVector2 = math::vec<2, T, ALIGNED_PRECISION>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using SimdVector3 = math::vec<3, T, ALIGNED_PRECISION>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using SimdVector4 = math::vec<4, T, ALIGNED_PRECISION>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using SimdQuaternion = math::qua<T, ALIGNED_PRECISION>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using SimdMatrix3x3 = math::mat<3, 3, T, ALIGNED_PRECISION>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using SimdMatrix4x4 = math::mat<4, 4, T, ALIGNED_PRECISION>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using FixedVector2 = math::vec<2, T, FIXED_PRECISION>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using FixedVector3 = math::vec<3, T, FIXED_PRECISION>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using FixedVector4 = math::vec<4, T, FIXED_PRECISION>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using FixedQuaternion = math::qua<T, FIXED_PRECISION>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using FixedMatrix3x3 = math::mat<3, 3, T, FIXED_PRECISION>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using FixedMatrix4x4 = math::mat<4, 4, T, FIXED_PRECISION>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Color = SimdVector4<T>;

	// @formatter:on
} // namespace power_ronin
