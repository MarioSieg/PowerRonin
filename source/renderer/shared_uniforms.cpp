#include "shared_uniforms.hpp"

namespace PowerRonin::Renderer
{
	void SharedUniforms::load_all()
	{
		this->ambient_color.load();
		this->light_dir.load();
		this->light_color.load();
	}

	void SharedUniforms::unload_all()
	{
		this->light_color.unload();
		this->light_dir.unload();
		this->ambient_color.unload();
	}
}
