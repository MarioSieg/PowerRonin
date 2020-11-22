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
	class Lambert final : public IShader<Material::Lambert> {
	public:
		explicit Lambert(GPU &_gpu) noexcept;

		virtual void load() override;
		virtual void unload() override;
		virtual void per_frame(const PerFrameBuffer &_buffer) override;
		virtual void draw(const Mesh &_mesh, const Material::Lambert &_mat) override;

	private:
		bgfx::UniformHandle u_s_tex_color_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_mat_color_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_light_dir_ = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_ambient_color = {bgfx::kInvalidHandle};
		bgfx::UniformHandle u_light_color = {bgfx::kInvalidHandle};
	};
}
