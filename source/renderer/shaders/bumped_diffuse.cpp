#include "bumped_diffuse.hpp"

namespace dce::renderer::shaders {
	BumpedDiffuseShader::BumpedDiffuseShader(GPU& _gpu) noexcept : IShader("bumped_diffuse", _gpu) {
	}

	void BumpedDiffuseShader::load() {
		IShader::load();
		this->diffuse_texture_sampler_.load();
		this->normal_map_sampler_.load();
		this->diffuse_color_.load();
	}

	void BumpedDiffuseShader::unload() {
		this->diffuse_color_.unload();
		this->normal_map_sampler_.unload();
		this->diffuse_texture_sampler_.unload();
		IShader::unload();
	}

	void BumpedDiffuseShader::draw(const Material::BumpedDiffuse& _mat, const Mesh& _mesh) const {
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.albedo, this->diffuse_texture_sampler_, 0);
		this->gpu_.set_texture(_mat.normal, this->normal_map_sampler_, 1);
		this->gpu_.draw(this->program_, SCENERY_VIEW);
	}
}
