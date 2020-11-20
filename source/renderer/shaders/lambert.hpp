// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: lambert.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 20.11.2020 12:23

#pragma once

#include "../ishader.hpp"

namespace dce::renderer {
	class Lambert final : public IShader<Material::Lambert, const Vector4<> &> {
	public:
		Lambert() noexcept;

		virtual void load() override;
		virtual void unload() override;
		virtual void draw(GPU &_gpu, const Mesh &_mesh, const Material::Lambert &_mat, const Vector4<> &_args) override;

	private:
		bgfx::UniformHandle u_s_tex_color_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_color_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_light_dir_ = {bgfx::kInvalidHandle};
	};
}
