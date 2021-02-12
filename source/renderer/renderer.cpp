#include "renderer.hpp"
#include "clocks.hpp"
#include "stats.hpp"
#include "../sysclock.hpp"
#include "../platform/platform.hpp"
#include "../../Include/PowerRonin/MathLib.hpp"
#include "../../Include/PowerRonin/Transform.hpp"
#include "../../Include/PowerRonin/MeshRenderer.hpp"
#include "../../Include/PowerRonin/VisitOverload.hpp"
#include "../../Include/PowerRonin/Sun.hpp"

namespace PowerRonin::Renderer
{
	RenderSystem::RenderSystem() : ISubsystem("RendererSystem", EVENTS), shader_bucket_(this->gpu_) { }

	void RenderSystem::OnPreStartup(Runtime& runtime)
	{
		this->gpu_.initialize_drivers(runtime.Config(), runtime.Protocol());

		this->shader_bucket_.load_all();
		this->shared_uniforms_.load_all();

		poll_limits(const_cast<Diagnostics&>(runtime.Diagnostics()));
		auto& viewport = runtime.RenderData().PrimaryViewport;
		if (viewport.z == .0F || viewport.w == .0F) [[likely]]
		{
			viewport.z = runtime.Config().Display.Resolution.Width;
			viewport.w = runtime.Config().Display.Resolution.Height;
			if (viewport.z == .0F || viewport.w == .0F) [[likely]]
			{
				throw MAKE_FATAL_ENGINE_EXCEPTION("Zero viewport size!");
			}
		}
		const auto& caps = *bgfx::getCaps();

		this->is_instancing_supported_ = !!(caps.supported & BGFX_CAPS_INSTANCING);
		this->tick_prev_ = get_high_precision_counter();
	}

	/* Prepare frame */
	void RenderSystem::OnPreTick(Runtime& _rt)
	{
#if AUTO_TEC
		if (_rt.RenderData().EnableWireframe) [[unlikely]]
		{
			bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_WIREFRAME);
		}
		else
		{
			bgfx::setDebug(BGFX_DEBUG_TEXT);
		}
#endif
		poll_stats(const_cast<Diagnostics&>(_rt.Diagnostics()));
		this->tick_prev_ = update_clocks(const_cast<Chrono&>(_rt.Chrono()), this->tick_prev_);
		this->update_camera(_rt);
		this->gpu_.set_viewport(Vector4<>{.0f, .0f, _rt.Config().Display.Resolution.Width, _rt.Config().Display.Resolution.Height}, FULLSCREEN_VIEW);
		this->gpu_.clear_view(FULLSCREEN_VIEW, BGFX_CLEAR_DEPTH | BGFX_CLEAR_COLOR, 1.F, 0x040404FF);
		this->gpu_.sort_draw_calls(FULLSCREEN_VIEW);
		this->gpu_.set_viewport(_rt.RenderData().PrimaryViewport, SCENERY_VIEW);
	}

	/* End frame */
	void RenderSystem::OnPostTick(Runtime& _rt)
	{
		this->render_scene(_rt);
		this->render_skybox(_rt.Scenery().config.lighting, _rt.RenderData());

#if AUTO_TEC
		if (_rt.Config().Editor.ShowStats) [[likely]]
		{
			render_stats(_rt);
		}
#endif

		this->gpu_.end_frame();
	}

	void RenderSystem::update_camera(Runtime& runtime) const
	{
		auto& data = runtime.RenderData();
		auto& current_view = data.ViewMatrix;
		auto& current_projection = data.ProjectionMatrix;

#if AUTO_TEC
		if (runtime.IsPlaying()) [[unlikely]]
		{
#endif
			auto& reg = runtime.Scenery().registry();
			const auto camera_entity = reg.view<Camera, Transform>().front();
			if (!reg.valid(camera_entity)) [[unlikely]]
			{
				return;
			}
			const auto& transform = reg.get<Transform>(camera_entity);
			auto& camera = reg.get<Camera>(camera_entity);
			camera.Recalculate(transform, data.PrimaryViewport.zw, current_view, current_projection);

#if AUTO_TEC
		}
		else
		{
			data.EditorCamera.Update(runtime.Input(), data.PrimaryViewport.z, data.PrimaryViewport.w, static_cast<float>(runtime.Chrono().DeltaTime));
			current_view = data.EditorCamera.ViewMatrix();
			current_projection = data.EditorCamera.ProjectionMatrix();
		}
#endif

		data.ViewProjectionMatrix = data.ProjectionMatrix * data.ViewMatrix;
		data.CameraFrustum.FromCameraMatrix(data.ViewProjectionMatrix);
		this->gpu_.set_camera(SCENERY_VIEW, data.ViewMatrix, data.ProjectionMatrix);
	}

	void RenderSystem::render_skybox(const Scenery::Configuration::Lighting& _lighting, RenderState& _data) const
	{
		this->gpu_.clear_view(SKYBOX_VIEW, BGFX_CLEAR_NONE);
		this->gpu_.set_viewport(_data.PrimaryViewport, SKYBOX_VIEW);

		// Create transform matrix:
		auto skybox_matrix = Math::identity<Matrix4x4<>>();

		// Copy and modify view matrix:
		_data.SkyboxViewMatrix = _data.ViewMatrix;

		// Remove translation:
		_data.SkyboxViewMatrix[3][0] = .0F;
		_data.SkyboxViewMatrix[3][1] = .0F;
		_data.SkyboxViewMatrix[3][2] = .0F;

		// Set camera:
		this->gpu_.set_camera(SKYBOX_VIEW, _data.SkyboxViewMatrix, _data.ProjectionMatrix);

		// Set transform:
		this->gpu_.set_transform(value_ptr(skybox_matrix));

		// Draw skybox:
		this->shader_bucket_.skybox.draw(std::get<Material::StaticSkybox>(_lighting.skybox_material->Properties), _lighting.skydome);
	}

	void RenderSystem::set_shared_uniforms(const Scenery::Configuration::Lighting& _lighting) const
	{
		const float orbit = calculate_sun_orbit(5, Math::radians(23.4f));
		const float hour = _lighting.sun.hour;
		const float latitude = _lighting.sun.latitude;
		const auto sun_dir = calculate_sun_dir(hour, latitude, orbit, Vector3<>(.0f, 1.f, .0f),
		                                       Vector3<>(1.f, .0f, .0f));

		this->shared_uniforms_.light_dir.set(sun_dir);
		this->shared_uniforms_.light_color.set(_lighting.sun.color);
		this->shared_uniforms_.ambient_color.set(_lighting.const_ambient_color);
	}

	void RenderSystem::render_scene(Runtime& _rt)
	{
		// Set per frame data for all shaders:
		this->set_shared_uniforms(_rt.Scenery().config.lighting);

		auto& diagnostics = const_cast<Diagnostics&>(_rt.Diagnostics());

		diagnostics.Graphics.SceneryMeshDrawCalls = 0;


		// Draw lambda function which renders an object:
		auto draw = [this, frustum = &_rt.RenderData().CameraFrustum, &diagnostics](Transform& _transform, MeshRenderer& _mesh_renderer)
		{
			// If the mesh renderer is not visible, skip it.
			if (!_mesh_renderer.IsVisible) [[unlikely]]
			{
				return;
			}

			// If the mesh renderer wants frustum culling and it is outside the frustum, skip it.
			if (_mesh_renderer.PerformFrustumCulling) [[likely]]
			{
				auto aabb_world_space = _mesh_renderer.Mesh->Aabb();
				aabb_world_space.Max += _transform.position;
				aabb_world_space.Min += _transform.position;
				if (!frustum->IsAabbVisible(aabb_world_space)) [[likely]]
				{
					return;
				}
			}

			// Set world transform matrix:
			this->gpu_.set_transform(_transform);

			const auto& mesh = _mesh_renderer.Mesh;
			const auto& mat = _mesh_renderer.Material->Properties;

			// Render each material with the corresponding shader:

			if (std::holds_alternative<Material::UnlitTextured>(mat)) [[unlikely]]
			{
				const auto& MaterialProperties = std::get<Material::UnlitTextured>(mat);
				this->shader_bucket_.unlit_textured.draw(MaterialProperties, mesh);
			}
			else if (std::holds_alternative<Material::Diffuse>(mat)) [[likely]]
			{
				const auto& MaterialProperties = std::get<Material::Diffuse>(mat);
				this->shader_bucket_.diffuse.draw(MaterialProperties, mesh);
			}
			else if (std::holds_alternative<Material::BumpedDiffuse>(mat)) [[likely]]
			{
				const auto& MaterialProperties = std::get<Material::BumpedDiffuse>(mat);
				this->shader_bucket_.bumped_diffuse.draw(MaterialProperties, mesh);
			}

			++diagnostics.Graphics.SceneryMeshDrawCalls;
		};

		// Iterate and draw:
		auto& registry = _rt.Scenery().registry();
		registry.view<Transform, MeshRenderer>().each(draw);
	}

	void RenderSystem::OnPostShutdown(Runtime& _rt)
	{
		this->shared_uniforms_.unload_all();
		this->shader_bucket_.unload_all();
		this->gpu_.shutdown_drivers();
	}
} // namespace PowerRonin::renderer // namespace PowerRonin::renderer
