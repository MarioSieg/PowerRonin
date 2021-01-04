#include "unlit_textured.hpp"

namespace power_ronin::renderer::shaders
{
	UnlitTexturedShader::UnlitTexturedShader(GPU& _gpu) noexcept : IShader("unlit_textured", _gpu) { }

	void UnlitTexturedShader::load()
	{
		IShader::load();
		this->texture_sampler_.load();
		this->tiling_offset_.load();
	}

	void UnlitTexturedShader::unload()
	{
		this->tiling_offset_.unload();
		this->texture_sampler_.unload();
		IShader::unload();
	}

	void UnlitTexturedShader::draw(const Material::UnlitTextured& _mat, const Mesh& _mesh) const
	{
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.albedo, this->texture_sampler_, 0);
		this->tiling_offset_.set(_mat.tiling_offset);
		this->gpu_.draw(this->program_, SCENERY_VIEW);
	}
}
