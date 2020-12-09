#pragma once

#include "mathlib.hpp"

namespace dce {
	/// <summary>
	/// Contains states and data for the renderer.
	/// </summary>
	class RenderData final {
	public:
		Vector2<> scenery_viewport_size = {.0f, .0f};
		Vector2<> scenery_viewport_position = { .0f, .0f };
		Matrix4x4<> view_matrix = {};
		Matrix4x4<> projection_matrix = {};
		bool enable_wireframe = false;
	};
}