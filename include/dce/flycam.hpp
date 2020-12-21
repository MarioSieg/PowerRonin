#pragma once

#include "mathlib.hpp"

namespace dce {
	class Input;

	/// <summary>
	/// Helper class for a flying editor camera.
	/// </summary>
	class FlyCam final {
	public:
		float move_speed = 8.F;
		float sensitivity = 0.5F;
		float fov = 80.F;
		float near_clip = 0.01F;
		float far_clip = 2000.F;
		float smoothness = 1.F;
		float clamp_y = 80.F;

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
		Vector2<> smooth_mouse_angles_ = {};
	};
}
