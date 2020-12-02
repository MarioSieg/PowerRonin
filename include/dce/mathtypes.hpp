// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

#define GLM_FORCE_INLINE
#define GLM_FORCE_INTRINSICS
#define GLM_FORCE_SWIZZLE
#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_SIZE_T_LENGTH
#define GLM_CONSTEXPR_SIMD
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
	namespace math {
		using namespace glm;
	}

	template <typename T = float>
	requires std::is_floating_point_v<T>
	||
	std::is_integral_v<T>
	using Vector2 = math::vec<2, T, math::defaultp>;

	template <typename T = float>
	requires std::is_floating_point_v<T>
	||
	std::is_integral_v<T>
	using Vector3 = math::vec<3, T, math::defaultp>;

	template <typename T = float>
	requires std::is_floating_point_v<T>
	||
	std::is_integral_v<T>
	using Vector4 = math::vec<4, T, math::defaultp>;

	template <typename T = float>
	requires std::is_floating_point_v<T>
	||
	std::is_integral_v<T>
	using Quaternion = math::qua<T, math::defaultp>;

	template <typename T = float>
	requires std::is_floating_point_v<T>
	||
	std::is_integral_v<T>
	using Matrix3x3 = math::mat<3, 3, T, math::defaultp>;

	template <typename T = float>
	requires std::is_floating_point_v<T>
	||
	std::is_integral_v<T>
	using Matrix4x4 = math::mat<4, 4, T, math::defaultp>;

	template <typename T = float>
	requires std::is_floating_point_v<T>
	||
	std::is_integral_v<T>
	using Color = Vector4<T>;
} // namespace dce
