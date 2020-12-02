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

#pragma once

#include "mathlib.hpp"

namespace dce {
	class Input;

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

		void update(const Input& _input, const float _viewport_x, const float _viewport_y, const float _delta_time);

	private:
		Matrix4x4<> view_ = {};
		Matrix4x4<> proj_ = {};
		Vector3<> eye_ = {};
		Vector3<> at_ = {};
		Vector3<> forward_ = {};
		Vector3<> left_ = {};
		Vector3<> dir_ = {.0f, .0f, 1.f};
		Vector2<> mouse_prev_ = {};
		Vector2<> mouse_angles_ = {};
	};
}
