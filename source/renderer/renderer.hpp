// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

#include "../../include/dce/core/kernel.hpp"
#include "../../include/dce/flycam.hpp"

#include "shader_bucket.hpp"
#include "gpu.hpp"

// UGLYY AAAA
extern const float *VIEW, *PROJ;

namespace dce {
	class MeshRenderer;
	class Transform;

	namespace renderer {
		class Renderer final : public core::ISubsystem {
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
			virtual auto on_pre_startup(Runtime& _rt) -> bool override;
			virtual auto on_pre_tick(Runtime& _rt) -> bool override;
			virtual auto on_post_tick([[maybe_unused]] Runtime& _rt) -> bool override;
			virtual auto on_post_shutdown([[maybe_unused]] Runtime& _rt) -> bool override;

			void render_skybox(const Scenery::Configuration::Lighting& _lighting, RenderData& _data) const;
			void set_per_frame_data(const Scenery::Configuration::Lighting& _lighting) const;
			void render_scene(Runtime& _rt);
			void update_camera(Runtime& _rt);

			FlyCam fly_cam_ = {};
			std::uint64_t tick_prev_ = 0;
			GPU gpu_ = {};
			ShaderBucket shader_bucket_;
		};
	} // namespace dce::renderer // namespace dce::renderer
}
