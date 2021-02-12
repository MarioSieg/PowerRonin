#pragma once

#include "../../Include/PowerRonin/core/Kernel.hpp"

#include "gpu.hpp"
#include "shader_bucket.hpp"
#include "shared_uniforms.hpp"

namespace PowerRonin
{
	class MeshRenderer;
	class Transform;

	namespace Renderer
	{
		class RenderSystem final : public Core::ISubsystem
		{
		public:
			/* Constructors, assignment operators, destructor */
			RenderSystem();
			RenderSystem(const RenderSystem&) = delete;
			RenderSystem(RenderSystem&&) = delete;
			auto operator=(const RenderSystem&) -> RenderSystem& = delete;
			auto operator=(RenderSystem&&) -> RenderSystem& = delete;
			~RenderSystem() override = default;

		private:
			/* Required kernel events */
			static constexpr auto EVENTS = Core::ServiceEvents::PreStartup | Core::ServiceEvents::PreTick |
				Core::ServiceEvents::PostTick | Core::ServiceEvents::PostShutdown;

			/* Kernel events */
			virtual void OnPreStartup(Runtime& runtime) override;
			virtual void OnPreTick(Runtime& _rt) override;
			virtual void OnPostTick([[maybe_unused]] Runtime& _rt) override;
			virtual void OnPostShutdown([[maybe_unused]] Runtime& _rt) override;

			void render_skybox(const Scenery::Configuration::Lighting& _lighting, RenderState& _data) const;
			void set_shared_uniforms(const Scenery::Configuration::Lighting& _lighting) const;
			void render_scene(Runtime& _rt);
			void update_camera(Runtime& runtime) const;

			std::uint64_t tick_prev_ = 0;
			GPU gpu_ = {};
			ShaderBucket shader_bucket_ = ShaderBucket{gpu_};
			SharedUniforms shared_uniforms_ = {};
			bool is_instancing_supported_ = false;
		};
	} // namespace PowerRonin::renderer // namespace PowerRonin::renderer
}
