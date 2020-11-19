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

namespace dce::renderer {
	enum class ShaderType {
		UNLIT
		, LAMBERT
	};

	class ShaderBucket final {
	public:
		void load_all();
		void unload_all();
		void render(GPU &_gpu, const MeshRenderer &_renderer);

	private:
		Unlit unlit_ = {};
	};
}
