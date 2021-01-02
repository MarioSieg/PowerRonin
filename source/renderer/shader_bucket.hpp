#pragma once

#include "shaders/unlit_textured.hpp"
#include "shaders/diffuse.hpp"
#include "shaders/bumped_diffuse.hpp"
#include "shaders/skybox.hpp"

namespace dce::renderer
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

		shaders::UnlitTexturedShader unlit_textured;
		shaders::DiffuseShader diffuse;
		shaders::BumpedDiffuseShader bumped_diffuse;
		shaders::SkyboxShader skybox;

	private:
		GPU& gpu_;
	};
}
