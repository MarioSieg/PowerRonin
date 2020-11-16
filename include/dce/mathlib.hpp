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
	using Vec2 = glm::vec2;
	using Vec3 = glm::vec3;
	using Vec4 = glm::vec4;
	using Quaternion = glm::quat;
	using Matrix4x4 = glm::mat4x4;
	namespace math = glm;
} // namespace dce
