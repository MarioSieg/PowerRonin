#pragma once

#include "../ishader.hpp"

namespace dce::renderer::shaders {
	class Diffuse final : public IShader {
	public:
		explicit Diffuse(GPU& _gpu) noexcept;

		void load() override;
		void unload() override;

		void per_frame(const Vector4<>& _sun_dir, const Color<>& _sun_color, const Color<>& _ambient_color) const;
		void per_object(const Mesh& _mesh, const Material::Diffuse& _mat) const;

	private:
		bgfx::UniformHandle u_s_tex_color_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_mat_color_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_light_dir_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_ambient_color_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_light_color_ = {bgfx::kInvalidHandle};
	};
}
