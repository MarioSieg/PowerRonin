#pragma once

#include "uniform.hpp"

namespace PowerRonin::Renderer
{
	/// <summary>
	/// Contains per frame shared uniforms which can be used by all shaders.
	/// </summary>
	class SharedUniforms final
	{
	public:
		SharedUniforms() = default;
		SharedUniforms(const SharedUniforms&) = delete;
		SharedUniforms(SharedUniforms&&) = delete;
		auto operator=(const SharedUniforms&) -> SharedUniforms& = delete;
		auto operator=(SharedUniforms&&) -> SharedUniforms& = delete;
		~SharedUniforms() = default;

		Uniform ambient_color = {"u_ambient_color", bgfx::UniformType::Vec4};
		Uniform light_dir = {"u_light_dir", bgfx::UniformType::Vec4};
		Uniform light_color = {"u_light_color", bgfx::UniformType::Vec4};

		void load_all();
		void unload_all();
	};
}
