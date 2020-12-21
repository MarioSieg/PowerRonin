#pragma once

#include "shaders/unlit.hpp"
#include "shaders/lambert.hpp"
#include "shaders/skybox.hpp"

namespace dce::renderer {
	enum class ShaderType {
		UNLIT,
		LAMBERT
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

		shaders::Unlit unlit;
		shaders::Lambert lambert;
		shaders::Skybox skybox;

	private:
		GPU& gpu_;
	};
}
