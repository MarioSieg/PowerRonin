// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#pragma once

#include "../../include/power_ronin/core/kernel.hpp"
#include "../../include/power_ronin/flycam.hpp"

#include "gpu.hpp"
#include "shader_bucket.hpp"
#include "shared_uniforms.hpp"

namespace power_ronin
{
	class MeshRenderer;
	class Transform;

	namespace renderer
	{
		class Renderer final : public core::ISubsystem
		{
		public:
			/* Constructors, assignment operators, destructor */
			Renderer();
			Renderer(const Renderer&) = delete;
			Renderer(Renderer&&) = delete;
			auto operator=(const Renderer&) -> Renderer& = delete;
			auto operator=(Renderer&&) -> Renderer& = delete;
			~Renderer() override = default;

		private:
			/* Required kernel events */
			static constexpr auto EVENTS = core::ServiceEvents::PRE_STARTUP | core::ServiceEvents::PRE_TICK |
				core::ServiceEvents::POST_TICK | core::ServiceEvents::POST_SHUTDOWN;

			/* Kernel events */
			auto on_pre_startup(Runtime& _rt) -> bool override;
			auto on_pre_tick(Runtime& _rt) -> bool override;
			auto on_post_tick([[maybe_unused]] Runtime& _rt) -> bool override;
			auto on_post_shutdown([[maybe_unused]] Runtime& _rt) -> bool override;

			void render_skybox(const Scenery::Configuration::Lighting& _lighting, RenderData& _data) const;
			void set_shared_uniforms(const Scenery::Configuration::Lighting& _lighting) const;
			void render_scene(Runtime& _rt);
			void update_camera(Runtime& _rt) const;

			std::uint64_t tick_prev_ = 0;
			GPU gpu_ = {};
			ShaderBucket shader_bucket_ = ShaderBucket{gpu_};
			SharedUniforms shared_uniforms_ = {};
			bool is_instancing_supported_ = false;
		};
	} // namespace power_ronin::renderer // namespace power_ronin::renderer
}
