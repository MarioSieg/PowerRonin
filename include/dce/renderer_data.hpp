#pragma once

#include "mathlib.hpp"

namespace dce {
	/// <summary>
	/// Contains states and data for the renderer.
	/// </summary>
	class RenderData final {
	public:
		SimdVector2<> scenery_viewport_size = {.0f, .0f};
		SimdVector2<> scenery_viewport_position = {.0f, .0f};
		SimdMatrix4x4<> view_matrix = {};
		SimdMatrix4x4<> projection_matrix = {};
		bool enable_wireframe = false;
	};
}
