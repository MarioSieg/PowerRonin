// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: mesh_renderer.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace dce {
	class MeshRenderer final {
	public:
		RRef<Mesh> mesh = {};
		RRef<Shader> shader = {};
		RRef<Texture> texture = {};
		bool is_visible = true;
	};
}
