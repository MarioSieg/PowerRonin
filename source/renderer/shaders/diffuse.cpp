#include "diffuse.hpp"

namespace power_ronin::renderer::shaders
{
	DiffuseShader::DiffuseShader(GPU& _gpu) noexcept : IShader("diffuse", _gpu) { }

	void DiffuseShader::load()
	{
		IShader::load();
		this->diffuse_texture_sampler_.load();
		this->tiling_offset_.load();
	}

	void DiffuseShader::unload()
	{
		this->tiling_offset_.unload();
		this->diffuse_texture_sampler_.unload();
		IShader::unload();
	}

	void DiffuseShader::draw(const Material::Diffuse& _mat, const Mesh& _mesh) const
	{
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.albedo, this->diffuse_texture_sampler_, 0);
		this->tiling_offset_.set(_mat.tiling_offset);
		this->gpu_.draw(this->program_, SCENERY_VIEW);
	}
}
