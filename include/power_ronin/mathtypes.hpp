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

#include "env.hpp"

#if SIMD_SSE
#define GLM_FORCE_SSE
#endif

#if SIMD_SSE2
#define GLM_FORCE_SSE2
#endif

#if SIMD_SSE3
#define GLM_FORCE_SSE3
#endif

#if SIMD_SSSE3
#define GLM_FORCE_SSSE3
#endif

#if SIMD_SSE4_1 || defined(SIMD_SSE4_2)
#define GLM_FORCE_SSE4
#endif

#if SIMD_AVX
#define GLM_FORCE_AVX
#endif

#if SIMD_AVX2
#define GLM_FORCE_AVX2
#endif

#if SIMD_AVX512
#define GLM_FORCE_AVX512
#endif

#define GLM_FORCE_INLINE
#define GLM_FORCE_SWIZZLE
#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_SIZE_T_LENGTH
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

namespace PowerRonin
{
	namespace Math
	{
		using namespace glm;
	}

	// @formatter:off

	constexpr auto AlignedPrecision = Math::aligned_highp;
	constexpr auto FixedPrecision = Math::mediump;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Vector2 = Math::vec<2, T, AlignedPrecision>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Vector3 = Math::vec<3, T, AlignedPrecision>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Vector4 = Math::vec<4, T, AlignedPrecision>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Quaternion = Math::qua<T, AlignedPrecision>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Matrix3x3 = Math::mat<3, 3, T, AlignedPrecision>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Matrix4x4 = Math::mat<4, 4, T, AlignedPrecision>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Vector2Fixed = Math::vec<2, T, FixedPrecision>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Vector3Fixed = Math::vec<3, T, FixedPrecision>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Vector4Fixed = Math::vec<4, T, FixedPrecision>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using QuaternionFixed = Math::qua<T, FixedPrecision>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Matrix3x3Fixed = Math::mat<3, 3, T, FixedPrecision>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Matrix4x4Fixed = Math::mat<4, 4, T, FixedPrecision>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Color = Vector4<T>;

	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	using Viewport = Vector4<T>;

	// @formatter:on
} // namespace PowerRonin
