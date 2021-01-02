#include "renderer.hpp"
#include "clocks.hpp"
#include "stats.hpp"
#include "../sysclock.hpp"
#include "../platform/platform.hpp"
#include "../../include/dce/mathlib.hpp"
#include "../../include/dce/transform.hpp"
#include "../../include/dce/mesh_renderer.hpp"
#include "../../include/dce/variant_visit_overloader.hpp"
#include "../../include/dce/sun.hpp"

namespace dce::renderer
{
	Renderer::Renderer() : ISubsystem("Renderer", EVENTS), shader_bucket_(this->gpu_) { }

	auto Renderer::on_pre_startup(Runtime& _rt) -> bool
	{
		if (!this->gpu_.initialize_drivers(_rt.config(), _rt.protocol()))
		{
			return false;
		}

		this->shader_bucket_.load_all();
		this->shared_uniforms_.load_all();

		poll_limits(const_cast<Diagnostics&>(_rt.diagnostics()));
		auto& viewport = _rt.render_data().scenery_viewport_size;
		if (viewport.x == .0F || viewport.y == .0F) [[likely]]
		{
			viewport.x = _rt.config().display.resolution.width;
			viewport.y = _rt.config().display.resolution.height;
			if (viewport.x == .0F || viewport.y == .0F) [[likely]]
			{
				return false;
			}
		}
		const auto& caps = *bgfx::getCaps();

		this->is_instancing_supported_ = !!(caps.supported & BGFX_CAPS_INSTANCING);
		this->tick_prev_ = get_high_precision_counter();

		return true;
	}

	/* Prepare frame */
	auto Renderer::on_pre_tick(Runtime& _rt) -> bool
	{
		if (_rt.render_data().enable_wireframe) [[unlikely]]
		{
			bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_WIREFRAME);
		}
		else
		{
			bgfx::setDebug(BGFX_DEBUG_TEXT);
		}
		poll_stats(const_cast<Diagnostics&>(_rt.diagnostics()));
		this->tick_prev_ = update_clocks(const_cast<Chrono&>(_rt.chrono()), this->tick_prev_);
		this->update_camera(_rt);
		this->gpu_.set_viewport(math::ZERO, {_rt.config().display.resolution.width, _rt.config().display.resolution.height}, FULLSCREEN_VIEW);
		this->gpu_.clear_view(FULLSCREEN_VIEW, BGFX_CLEAR_DEPTH | BGFX_CLEAR_COLOR, 1.F, 0x040404FF);
		this->gpu_.sort_draw_calls(FULLSCREEN_VIEW);
		this->gpu_.set_viewport(_rt.render_data().scenery_viewport_position, _rt.render_data().scenery_viewport_size,
		                        SCENERY_VIEW);
		return true;
	}

	/* End frame */
	auto Renderer::on_post_tick(Runtime& _rt) -> bool
	{
		this->render_scene(_rt);
		this->render_skybox(_rt.scenery().config.lighting, _rt.render_data());

		if (_rt.config().editor.show_stats) [[likely]]
		{
			render_stats(_rt);
		}

		this->gpu_.end_frame();
		return true;
	}

	void Renderer::update_camera(Runtime& _rt) const
	{
		_rt.render_data().editor_camera.update(_rt.input(), _rt.render_data().scenery_viewport_size.x, _rt.render_data().scenery_viewport_size.y,
		                                       static_cast<float>(_rt.chrono().delta_time));
		auto& data = _rt.render_data();
		data.view_matrix = _rt.render_data().editor_camera.view_matrix();
		data.projection_matrix = _rt.render_data().editor_camera.projection_matrix();
		data.view_projection_matrix = data.projection_matrix * data.view_matrix;
		data.camera_frustum.from_camera_matrix(data.view_projection_matrix);
		this->gpu_.set_camera(SCENERY_VIEW, data.view_matrix, data.projection_matrix);
	}

	void Renderer::render_skybox(const Scenery::Configuration::Lighting& _lighting, RenderData& _data) const
	{
		this->gpu_.clear_view(SKYBOX_VIEW, BGFX_CLEAR_NONE);
		this->gpu_.set_viewport(_data.scenery_viewport_position, _data.scenery_viewport_size, SKYBOX_VIEW);

		// Create transform matrix:
		auto skybox_matrix = math::identity<SimdMatrix4x4<>>();

		// Copy and modify view matrix:
		_data.skybox_view_matrix = _data.view_matrix;

		// Remove translation:
		_data.skybox_view_matrix[3][0] = .0F;
		_data.skybox_view_matrix[3][1] = .0F;
		_data.skybox_view_matrix[3][2] = .0F;

		// Set camera:
		this->gpu_.set_camera(SKYBOX_VIEW, _data.skybox_view_matrix, _data.projection_matrix);

		// Set transform:
		this->gpu_.set_transform(value_ptr(skybox_matrix));

		// Draw skybox:
		this->shader_bucket_.skybox.draw(std::get<Material::StaticSkybox>(_lighting.skybox_material->properties), _lighting.skydome);
	}

	void Renderer::set_shared_uniforms(const Scenery::Configuration::Lighting& _lighting) const
	{
		const float orbit = calculate_sun_orbit(5, math::radians(23.4f));
		const float hour = _lighting.sun.hour;
		const float latitude = _lighting.sun.latitude;
		const auto sun_dir = calculate_sun_dir(hour, latitude, orbit, SimdVector3<>(.0f, 1.f, .0f),
		                                       SimdVector3<>(1.f, .0f, .0f));

		this->shared_uniforms_.light_dir.set(sun_dir);
		this->shared_uniforms_.light_color.set(_lighting.sun.color);
		this->shared_uniforms_.ambient_color.set(_lighting.const_ambient_color);
	}

	void Renderer::render_scene(Runtime& _rt)
	{
		// Set per frame data for all shaders:
		this->set_shared_uniforms(_rt.scenery().config.lighting);

		auto& diagnostics = const_cast<Diagnostics&>(_rt.diagnostics());

		diagnostics.graphics.scenery_mesh_drawcalls = 0;


		// Draw lambda function which render_stats an object:
		auto draw = [this, frustum = &_rt.render_data().camera_frustum, &diagnostics](Transform& _transform, MeshRenderer& _mesh_renderer)
		{
			// If the mesh renderer is not visible, skip it.
			if (!_mesh_renderer.is_visible) [[unlikely]]
			{
				return;
			}

			// If the mesh renderer wants frustum culling and it is outside the frustum, skip it.
			if (_mesh_renderer.perform_frustum_culling) [[likely]]
			{

				auto aabb_world_space = _mesh_renderer.mesh->aabb();
				aabb_world_space.max += _transform.position;
				aabb_world_space.min += _transform.position;
				if (!frustum->is_aabb_visible(aabb_world_space)) [[likely]]
				{
					return;
				}
			}

			// Set world transform matrix:
			this->gpu_.set_transform(_transform);

			const auto& mesh = _mesh_renderer.mesh;
			const auto& mat = _mesh_renderer.material->properties;

			// Render each material with the corresponding shader:

			if (std::holds_alternative<Material::UnlitTextured>(mat)) [[unlikely]]
			{
				const auto& properties = std::get<Material::UnlitTextured>(mat);
				this->shader_bucket_.unlit_textured.draw(properties, mesh);
			}
			else if (std::holds_alternative<Material::Diffuse>(mat)) [[likely]]
			{
				const auto& properties = std::get<Material::Diffuse>(mat);
				this->shader_bucket_.diffuse.draw(properties, mesh);
			}
			else if (std::holds_alternative<Material::BumpedDiffuse>(mat)) [[likely]]
			{
				const auto& properties = std::get<Material::BumpedDiffuse>(mat);
				this->shader_bucket_.bumped_diffuse.draw(properties, mesh);
			}

			++diagnostics.graphics.scenery_mesh_drawcalls;
		};

		// Iterate and draw:
		auto& registry = _rt.scenery().registry();
		registry.view<Transform, MeshRenderer>().each(draw);
	}

	auto Renderer::on_post_shutdown(Runtime& _rt) -> bool
	{
		this->shared_uniforms_.unload_all();
		this->shader_bucket_.unload_all();
		this->gpu_.shutdown_drivers();
		return true;
	}
} // namespace dce::renderer // namespace dce::renderer
