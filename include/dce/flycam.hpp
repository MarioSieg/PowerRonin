#pragma once

#include "mathlib.hpp"

namespace dce {
	class Input;

	/// <summary>
	/// Helper class for a flying editor camera.
	/// </summary>
	class EditorCamera final {
	public:
		float move_speed = 8.F;
		float sensitivity = 0.5F;
		float fov = 80.F;
		float near_clip = 0.01F;
		float far_clip = 1000.F;
		float smoothness = 1.F;
		float clamp_y = 80.F;

		[[nodiscard]] auto projection_matrix() const noexcept -> const SimdMatrix4x4<>&;

		[[nodiscard]] auto view_matrix() const noexcept -> const SimdMatrix4x4<>&;

		[[nodiscard]] auto position() const noexcept -> const SimdVector3<>&;

		void position(const SimdVector3<>& _position) noexcept;

		[[nodiscard]] auto look_at() const noexcept -> const SimdVector3<>&;

		void look_at(const SimdVector3<>&) noexcept;

		auto look_at_dir() const noexcept -> const SimdVector3<>&;

		void look_at_dir(const SimdVector3<>& _dir) noexcept;

		void update(const Input& _input, const float _viewport_x, const float _viewport_y, const float _delta_time);

	private:
		SimdMatrix4x4<> view_ = {};
		SimdMatrix4x4<> proj_ = {};
		SimdVector3<> eye_ = {};
		SimdVector3<> at_ = {};
		SimdVector3<> forward_ = {};
		SimdVector3<> left_ = {};
		SimdVector3<> dir_ = {.0f, .0f, 1.f};
		SimdVector2<> mouse_prev_ = {};
		SimdVector2<> mouse_angles_ = {};
		SimdVector2<> smooth_mouse_angles_ = {};
	};
}
