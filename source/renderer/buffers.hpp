// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: buffers.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 21.11.2020 23:15

#pragma once

#include "../../include/dce/mathlib.hpp"

namespace dce::renderer {

	/// <summary>
	/// Data which will be submitted to the GPU each frame.
	/// </summary>
	struct PerFrameBuffer final {
		Vector4<> sun_color;
		Vector4<> sun_dir;
		Vector4<> ambient_color;
	};

	/// <summary>
	/// Data which will be submitted to the GPU for each material.
	/// </summary>
	struct PerMaterialBuffer final { };

	/// <summary>
	/// Data which will be submitted to the GPU for each object.
	/// </summary>
	struct PerObjectBuffer final { };
}
