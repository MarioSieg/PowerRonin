// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: renderer.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

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
			Renderer(const Renderer &) = delete;
			Renderer(Renderer &&) = delete;
			auto operator=(const Renderer &) -> Renderer& = delete;
			auto operator=(Renderer &&) -> Renderer& = delete;
			~Renderer() override = default;

		private:
			/* Required kernel events */
			static constexpr auto EVENTS = core::ServiceEvents::PRE_STARTUP | core::ServiceEvents::PRE_TICK |
				core::ServiceEvents::POST_TICK | core::ServiceEvents::POST_SHUTDOWN;

			/* Kernel events */
			virtual auto on_pre_startup(State & /*_state*/) -> bool override;
			virtual auto on_pre_tick(State & /*_state*/) -> bool override;
			virtual auto on_post_tick(State & /*unused*/) -> bool override;
			virtual auto on_post_shutdown(State & /*unused*/) -> bool override;

			std::uint64_t tick_prev_ = 0;
			FlyCam fly_cam_ = {};
			GPU gpu_ = {};
			ShaderBucket shader_bucket_ = {};
		};
	} // namespace dce::renderer // namespace dce::renderer
}
