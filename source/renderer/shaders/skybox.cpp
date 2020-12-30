#include "skybox.hpp"

namespace dce::renderer::shaders {

	SkyboxShader::SkyboxShader(GPU& _gpu) noexcept : IShader("skybox", _gpu) {
	}

	void SkyboxShader::load() {
		IShader::load();
		this->cubemap_sampler_.load();
	}

	void SkyboxShader::unload() {
		this->cubemap_sampler_.unload();
		IShader::unload();
	}

	void SkyboxShader::draw(const Material::StaticSkybox& _mat, const Mesh& _mesh) const {
		this->gpu_.set_mesh_buffer(_mesh);
		this->gpu_.set_texture(_mat.cubemap, this->cubemap_sampler_, 0);
		this->gpu_.draw(this->program_, SKYBOX_VIEW, BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_LESS);
	}
}
