// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: unlit.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 19.11.2020 18:32

#pragma once

#include "../ishader.hpp"

namespace dce::renderer {
	class Unlit final : public IShader<Material::Unlit> {
	public:
		explicit Unlit(GPU &_gpu) noexcept;

		virtual void load() override;
		virtual void unload() override;
		virtual void draw(const Mesh &_mesh, const Material::Unlit &_mat) override;

	private:
		bgfx::UniformHandle u_s_tex_color_ = {bgfx::kInvalidHandle};
	};
}
