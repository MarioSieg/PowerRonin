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
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
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

		return true;
	}

	/* Prepare frame */
	auto Renderer::on_pre_tick(Runtime& _rt) -> bool {
		get_runtime_stats(const_cast<Diagnostics&>(_rt.diagnostics()));
		this->tick_prev_ = update_clocks(const_cast<Chrono&>(_rt.chrono()), this->tick_prev_);
		this->gpu_.clear_view(SCENERY_VIEW);
		this->gpu_.sort_draw_calls(SCENERY_VIEW);
		return true;
	}

	/* End frame */
	auto Renderer::on_post_tick(Runtime& _rt) -> bool {
		const auto& lighting = _rt.scenery().config.lighting;
		{
			// Update camera and set matrices:
			this->update_camera(_rt);

			// Set per frame data for all shaders:
			this->set_per_frame_data(_rt.scenery().config.lighting);

			// Draw lambda function which render an object:
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
					           },

					           // Render with lambert material:
					           [this, mesh](const Material::Lambert& _material) {
						           this->shader_bucket_.lambert.per_object(mesh, _material);
					           },
				           }, _mesh_renderer.material->get_properties());
			};

			// Iterate and draw:
			auto& registry = _rt.scenery().registry();
			registry.view<Transform, MeshRenderer>().each(draw);
		}

		this->gpu_.clear_view(SKYBOX_VIEW, BGFX_CLEAR_NONE);
		this->draw_skybox(lighting);

		this->gpu_.end_frame();
		return true;
	}

	auto Renderer::on_post_shutdown(Runtime& _rt) -> bool {
		this->shader_bucket_.unload_all();
		this->gpu_.shutdown_drivers();
		return true;
	}

	void Renderer::update_camera(const Runtime& _rt) {
		this->fly_cam_.update(_rt.input(), _rt.config().display.width, _rt.config().display.height, static_cast<float>(_rt.chrono().delta_time));
		this->view_ = this->fly_cam_.get_view_matrix();
		this->projection_ = this->fly_cam_.get_projection_matrix();
		this->gpu_.set_camera(SCENERY_VIEW, this->view_, this->projection_);
	}

	void Renderer::draw_skybox(const Scenery::Configuration::Lighting& _lighting) {
		// Create transform matrix:
		auto skybox_matrix = math::identity<Matrix4x4<>>();
		skybox_matrix = scale(skybox_matrix, Vector3<>{10});

		// Remove translation:
		this->view_[3][0] = .0f;
		this->view_[3][1] = .0f;
		this->view_[3][2] = .0f;

		// Set camera:
		this->gpu_.set_camera(SKYBOX_VIEW, this->view_, this->projection_);

		// Set transform:
		this->gpu_.set_transform(value_ptr(skybox_matrix));

		// Draw skybox:
		this->shader_bucket_.skybox.per_frame(_lighting.skybox_cubemap, _lighting.skydome);
	}

	void Renderer::set_per_frame_data(const Scenery::Configuration::Lighting& _lighting) const {
		const auto sun_dir = Vector4<>(calculate_sun_dir(_lighting.sun.hour, _lighting.sun.latitude, calculate_sun_orbit(6, math::radians(23.4f)), math::UP, math::NORTH), 1.f);
		this->shader_bucket_.lambert.per_frame(sun_dir, _lighting.sun.color, _lighting.const_ambient_color);
	}
} // namespace dce::renderer // namespace dce::renderer
