// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: flycam.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

#include "mathlib.hpp"

namespace dce {
	class State;

	/* Header only helper class for a flying editor camera. */
	class FlyCam final {
	public:
		float move_speed = 3.f;
		float fast_move_speed = 6.f;
		float sensitivity = 100.f;
		float fov = 80.0f;
		float near_clip = 0.01f;
		float far_clip = 2000.0f;

		[[nodiscard]] auto get_projection_matrix() const noexcept -> const Matrix4x4<>&;

		[[nodiscard]] auto get_view_matrix() const noexcept -> const Matrix4x4<>&;

		[[nodiscard]] auto get_eye_vector() const noexcept -> const Vector3<>&;

		void set_position(const Vector3<>& _position) noexcept;

		[[nodiscard]] auto get_direction_vector() const noexcept -> const Vector3<>&;

		[[nodiscard]] auto get_upwards_vector() const noexcept -> const Vector3<>&;

		void update(const State& _state);

	private:
		Matrix4x4<> view_ = {};
		Matrix4x4<> proj_ = {};
		Vector3<> eye_ = {};
		Vector3<> at_ = {};
		Vector3<> up_ = {.0f, 1.f, .0f};
		Vector3<> forward_ = {};
		Vector3<> left_ = {};
		Vector3<> dir_ = {.0f, .0f, 1.f};
		Vector2<> mouse_prev_ = {};
		Vector2<> mouse_angles_ = {};
	};
}
