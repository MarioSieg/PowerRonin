#pragma once

#include "shaders/unlit_textured.hpp"
#include "shaders/diffuse.hpp"
#include "shaders/bumped_diffuse.hpp"
#include "shaders/skybox.hpp"

namespace PowerRonin::Renderer
{
	class ShaderBucket final
	{
	public:
		explicit ShaderBucket(GPU& _gpu) noexcept;
		ShaderBucket(const ShaderBucket&) = delete;
		ShaderBucket(ShaderBucket&&) = delete;
		auto operator=(const ShaderBucket&) = delete;
		auto operator=(ShaderBucket&&) = delete;
		~ShaderBucket() = default;

		void load_all();
		void unload_all();

		Shaders::UnlitTexturedShader unlit_textured;
		Shaders::DiffuseShader diffuse;
		Shaders::BumpedDiffuseShader bumped_diffuse;
		Shaders::SkyboxShader skybox;

	private:
		GPU& gpu_;
	};
}
