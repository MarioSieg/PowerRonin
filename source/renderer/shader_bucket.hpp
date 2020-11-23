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
#include "buffers.hpp"

namespace dce::renderer {
	enum class ShaderType {
		UNLIT
		, LAMBERT
	};

	class ShaderBucket final {
	public:
		explicit ShaderBucket(GPU& _gpu) noexcept;
		ShaderBucket(const ShaderBucket&) = delete;
		ShaderBucket(ShaderBucket&&) = delete;
		auto operator=(const ShaderBucket&) = delete;
		auto operator=(ShaderBucket&&) = delete;
		~ShaderBucket() = default;

		void load_all();
		void unload_all();
		void per_frame(const PerFrameBuffer& _buffer);
		void per_material(const PerMaterialBuffer& _buffer);
		void per_object(const PerObjectBuffer& _buffer);
		void render(GPU& _gpu, const MeshRenderer& _renderer);

	private:
		Unlit unlit_;
		Lambert lambert_;
	};
}
