#include "shader_bucket.hpp"

namespace PowerRonin::Renderer
{
	ShaderBucket::ShaderBucket(GPU& _gpu) noexcept : unlit_textured(_gpu), diffuse(_gpu), bumped_diffuse(_gpu), skybox(_gpu),
	                                                 gpu_(_gpu) { }

	void ShaderBucket::load_all()
	{
		this->unlit_textured.load();
		this->diffuse.load();
		this->bumped_diffuse.load();
		this->skybox.load();
	}

	void ShaderBucket::unload_all()
	{
		this->skybox.unload();
		this->bumped_diffuse.unload();
		this->diffuse.unload();
		this->unlit_textured.unload();
	}
}
