// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: shader_bucket.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 19.11.2020 18:33

#pragma once

#include "shaders/unlit.hpp"
#include "shaders/lambert.hpp"

namespace dce::renderer {
	enum class ShaderType {
		UNLIT
		, LAMBERT
	};

	struct RenderParams final {
		Vector4<> light_dir = {0, 1, 0, 1};
	};

	class ShaderBucket final {
	public:
		void load_all();
		void unload_all();
		void render(GPU &_gpu, const MeshRenderer &_renderer, const RenderParams &_props);

	private:
		Unlit unlit_ = {};
		Lambert lambert_ = {};
	};
}
