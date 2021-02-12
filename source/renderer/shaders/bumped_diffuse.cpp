#include "bumped_diffuse.hpp"

namespace PowerRonin::Renderer::Shaders
{
	BumpedDiffuseShader::BumpedDiffuseShader(GPU& _gpu) noexcept : IShader("bumped_diffuse", _gpu) { }

	void BumpedDiffuseShader::load()
	{
		IShader::load();
		this->diffuse_texture_sampler_.load();
		this->normal_map_sampler_.load();
		this->tiling_offset_.load();
	}

	void BumpedDiffuseShader::unload()
	{
		this->tiling_offset_.unload();
		this->normal_map_sampler_.unload();
		this->diffuse_texture_sampler_.unload();
		IShader::unload();
	}

	void BumpedDiffuseShader::draw(const Material::BumpedDiffuse& _mat, const Mesh& _mesh) const
	{
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.Albedo, this->diffuse_texture_sampler_, 0);
		this->gpu_.set_texture(_mat.Normal, this->normal_map_sampler_, 1);
		this->tiling_offset_.set(_mat.TilingOffset);
		this->gpu_.draw(this->program_, SCENERY_VIEW);
	}
}
