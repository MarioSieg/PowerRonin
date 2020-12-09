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

#include "renderer.hpp"

#include "clocks.hpp"
#include "stats.hpp"

#include "../platform/platform.hpp"
#include "../../include/dce/mathlib.hpp"
#include "../../include/dce/transform.hpp"
#include "../../include/dce/mesh_renderer.hpp"
#include "../../include/dce/variant_visit_overloader.hpp"
#include "../../include/dce/sun.hpp"

const float *VIEW, *PROJ;

namespace dce::renderer {
	Renderer::Renderer() : ISubsystem("Renderer", EVENTS), shader_bucket_(this->gpu_) { }

	auto Renderer::on_pre_startup(Runtime& _rt) -> bool {
		if (!this->gpu_.initialize_drivers(_rt.config(), _rt.protocol())) {
			return false;
		}

		this->shader_bucket_.load_all();

		get_limits(const_cast<Diagnostics&>(_rt.diagnostics()));

		this->fly_cam_.set_position({0.0f, 0.0f, -5.0f});

		auto& viewport = _rt.render_data().scenery_viewport_size;
		[[likely]] if (!viewport.x || !viewport.y) {
			viewport.x = _rt.config().display.width;
			viewport.y = _rt.config().display.height;
			[[likely]] if (!viewport.x || !viewport.y) {
				return false;
			}
		}

		return true;
	}

	/* Prepare frame */
	auto Renderer::on_pre_tick(Runtime& _rt) -> bool {
		[[unlikely]] if (_rt.render_data().enable_wireframe) {
			bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_WIREFRAME);
		}
		else {
			bgfx::setDebug(BGFX_DEBUG_TEXT);
		}
		get_runtime_stats(const_cast<Diagnostics&>(_rt.diagnostics()));
		this->tick_prev_ = update_clocks(const_cast<Chrono&>(_rt.chrono()), this->tick_prev_);
		this->gpu_.clear_view(SCENERY_VIEW);
		this->gpu_.set_viewport(_rt.render_data().scenery_viewport_position, _rt.render_data().scenery_viewport_size, SCENERY_VIEW);
		this->gpu_.sort_draw_calls(SCENERY_VIEW);
		return true;
	}

	/* End frame */
	auto Renderer::on_post_tick(Runtime& _rt) -> bool {
		this->render_scene(_rt);
		this->render_skybox(_rt.scenery().config.lighting, _rt.render_data());

		[[unlikely]] if (_rt.config().overlay.show_stats) {
			render_stats(_rt);
		}

		this->gpu_.end_frame();
		return true;
	}

	void Renderer::update_camera(Runtime& _rt) {
		this->fly_cam_.update(_rt.input(), _rt.render_data().scenery_viewport_size.x, _rt.render_data().scenery_viewport_size.y
		                      , static_cast<float>(_rt.chrono().delta_time));
		auto& data = _rt.render_data();
		data.view_matrix = this->fly_cam_.get_view_matrix();
		data.projection_matrix = this->fly_cam_.get_projection_matrix();
		this->gpu_.set_camera(SCENERY_VIEW, data.view_matrix, data.projection_matrix);
	}

	void Renderer::render_skybox(const Scenery::Configuration::Lighting& _lighting, RenderData& _data) const {
		this->gpu_.clear_view(SKYBOX_VIEW, BGFX_CLEAR_NONE);
		this->gpu_.set_viewport(_data.scenery_viewport_position, _data.scenery_viewport_size, SKYBOX_VIEW);
		// Create transform matrix:
		auto skybox_matrix = math::identity<Matrix4x4<>>();
		skybox_matrix = scale(skybox_matrix, Vector3<>{10});
		// Remove translation:
		_data.view_matrix[3][0] = .0f;
		_data.view_matrix[3][1] = .0f;
		_data.view_matrix[3][2] = .0f;

		// Set camera:
		this->gpu_.set_camera(SKYBOX_VIEW, _data.view_matrix, _data.projection_matrix);

		// Set transform:
		this->gpu_.set_transform(value_ptr(skybox_matrix));

		// Draw skybox:
		this->shader_bucket_.skybox.per_frame(_lighting.skybox_cubemap, _lighting.skydome);
	}

	void Renderer::set_per_frame_data(const Scenery::Configuration::Lighting& _lighting) const {
		const auto orbit = calculate_sun_orbit(6, math::radians(23.4f));
		const auto sun_dir = Vector4<>(calculate_sun_dir(_lighting.sun.hour, _lighting.sun.latitude, orbit, math::UP, math::NORTH)
		                               , 1.f);
		this->shader_bucket_.lambert.per_frame(sun_dir, _lighting.sun.color, _lighting.const_ambient_color);
	}

	void Renderer::render_scene(Runtime& _rt) {
		// Update camera and set matrices:
		this->update_camera(_rt);

		// Set per frame data for all shaders:
		this->set_per_frame_data(_rt.scenery().config.lighting);

		// Draw lambda function which render_stats an object:
		auto draw = [this](Transform& _transform, MeshRenderer& _mesh_renderer) {

			// If the mesh renderer is not visible, skip it.
			[[unlikely]] if (!_mesh_renderer.is_visible) {
				return;
			}

			// Set world transform matrix:
			this->gpu_.set_transform(_transform);

			// Get a reference to the mesh to capture.
			const auto& mesh = _mesh_renderer.mesh;

			// Render each material with the corresponding shader:
			std::visit(overload{

				           // Render with unlit material:
				           [this, mesh](const Material::Unlit& _material) {
					           this->shader_bucket_.unlit.per_object(mesh, _material);
				           }
				           ,

				           // Render with lambert material:
				           [this, mesh](const Material::Lambert& _material) {
					           this->shader_bucket_.lambert.per_object(mesh, _material);
				           }
				           ,
			           }, _mesh_renderer.material->get_properties());
		};

		// Iterate and draw:
		auto& registry = _rt.scenery().registry();
		registry.view<Transform, MeshRenderer>().each(draw);
	}

	auto Renderer::on_post_shutdown(Runtime& _rt) -> bool {
		this->shader_bucket_.unload_all();
		this->gpu_.shutdown_drivers();
		return true;
	}
} // namespace dce::renderer // namespace dce::renderer
