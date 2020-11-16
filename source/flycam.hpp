// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: flycam.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "../include/dce/mathlib.hpp"

namespace dce {
	/* Helper class for a flying editor camera. */
	class FlyCam final {
	public:
		float move_speed = 3.f;
		float fast_move_speed = 6.f;
		float sensitivity = 100.f;
		float fov = 60.0f;
		float near_clip = 0.1f;
		float far_clip = 100.0f;

		[[nodiscard]] auto get_projection_matrix() const noexcept -> const Matrix4x4&;

		[[nodiscard]] auto get_view_matrix() const noexcept -> const Matrix4x4&;

		[[nodiscard]] auto get_eye_vector() const noexcept -> const Vec3&;

		void set_position(const Vec3 &_position) noexcept;

		[[nodiscard]] auto get_direction_vector() const noexcept -> const Vec3&;

		[[nodiscard]] auto get_upwards_vector() const noexcept -> const Vec3&;

		void update(const float _delta_time);

	private:
		Matrix4x4 view_ = {};
		Matrix4x4 proj_ = {};
		Vec3 eye_ = {};
		Vec3 at_ = {};
		Vec3 up_ = {.0f, 1.f, .0f};
		Vec3 forward_ = {};
		Vec3 left_ = {};
		Vec2 mouse_prev_ = {};
		Vec2 mouse_angles_ = {};
	};
}
