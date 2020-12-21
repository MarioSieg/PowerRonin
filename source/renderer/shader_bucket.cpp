#include "shader_bucket.hpp"

namespace dce::renderer {
	ShaderBucket::ShaderBucket(GPU& _gpu) noexcept : unlit(_gpu), lambert(_gpu), skybox(_gpu), gpu_(_gpu) {
	}

	void ShaderBucket::load_all() {
		this->unlit.load();
		this->lambert.load();
		this->skybox.load();
	}

	void ShaderBucket::unload_all() {
		this->skybox.unload();
		this->lambert.unload();
		this->unlit.unload();
	}
}
