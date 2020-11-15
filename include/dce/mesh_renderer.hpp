// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: mesh_renderer.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 13.11.2020 22:56

#pragma once

#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace dce {
	class MeshRenderer final {
	public:
		ResourceHandle<Mesh> mesh = {};
		ResourceHandle<Shader> shader = {};
		ResourceHandle<Texture> texture = {};
		bool is_visible = true;
	};
}
