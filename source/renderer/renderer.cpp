// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: renderer.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "renderer.hpp"

#include "clocks.hpp"
#include "stats.hpp"

#include "../platform/platform.hpp"
#include "../../include/dce/mathlib.hpp"
#include "../../include/dce/transform.hpp"
#include "../../include/dce/mesh_renderer.hpp"
#include "../../include/dce/sun.hpp"

const float* VIEW,* PROJ;

namespace dce::renderer {
	Renderer::Renderer() : ISubsystem("Renderer", EVENTS), shader_bucket_(this->gpu_) { }

	auto Renderer::on_pre_startup(State& _state) -> bool {

		if (!this->gpu_.initialize_drivers(_state.config(), _state.protocol())) {
			return false;
		}

		this->shader_bucket_.load_all();

		get_limits(const_cast<Diagnostics &>(_state.diagnostics()));

		this->fly_cam_.set_position({0.0f, 0.0f, -5.0f});

		return true;
	}

	/* Prepare frame */
	auto Renderer::on_pre_tick(State& _state) -> bool {
		get_runtime_stats(const_cast<Diagnostics &>(_state.diagnostics()));
		this->tick_prev_ = update_clocks(const_cast<Chrono &>(_state.chrono()), this->tick_prev_);
		this->gpu_.begin_frame();
		return true;
	}

	/* End frame */
	auto Renderer::on_post_tick(State& _state) -> bool {
		this->gpu_.sort_drawcalls();
		{
			this->fly_cam_.update(_state);
			VIEW = value_ptr(this->fly_cam_.get_view_matrix());
			PROJ = value_ptr(this->fly_cam_.get_projection_matrix());
			this->gpu_.set_camera(this->fly_cam_.get_view_matrix(), this->fly_cam_.get_projection_matrix());


			this->set_per_frame_buffer(_state.scenery().config);


			auto draw = [this](Transform& _transform, MeshRenderer& _mesh_renderer) {
				[[likely]] if (_mesh_renderer.is_visible) {
					this->gpu_.set_transform(_transform);
					this->shader_bucket_.render(this->gpu_, _mesh_renderer);
				}
			};

			auto& registry = _state.scenery().registry();
			registry.view<Transform, MeshRenderer>().each(draw);
		}
		this->gpu_.end_frame();
		return true;
	}

	auto Renderer::on_post_shutdown(State& _state) -> bool {
		this->shader_bucket_.unload_all();
		this->gpu_.shutdown_drivers();
		return true;
	}

	void Renderer::set_per_frame_buffer(const Scenery::Configuration& _config) {

		const float delta = calculate_sun_orbit(6, math::radians(23.4f));
		const auto sun_dir = calculate_sun_dir(_config.lighting.sun.hour, _config.lighting.sun.latitude, delta, math::UP, math::NORTH);

		const PerFrameBuffer per_frame = {.sun_color = _config.lighting.sun.color.xyzz, .sun_dir = sun_dir.xyzz, .ambient_color = _config.lighting.const_ambient_color.xyzz,};

		this->shader_bucket_.per_frame(per_frame);
	}
} // namespace dce::renderer // namespace dce::renderer
