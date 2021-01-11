// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#pragma once

#include "mathlib.hpp"

namespace power_ronin
{
	class Input;

	/// <summary>
	/// Helper class for a flying editor camera.
	/// </summary>
	class EditorCamera final
	{
	public:
		float move_speed = 8.F;
		float sensitivity = 0.5F;
		float fov = 80.F;
		float near_clip = 0.01F;
		float far_clip = 1000.F;
		float smoothness = 1.F;
		float clamp_y = 80.F;

		[[nodiscard]] auto projection_matrix() const noexcept -> const SMat4x4<>&;

		[[nodiscard]] auto view_matrix() const noexcept -> const SMat4x4<>&;

		[[nodiscard]] auto position() const noexcept -> const SVec3<>&;

		void position(const SVec3<>& _position) noexcept;

		[[nodiscard]] auto look_at() const noexcept -> const SVec3<>&;

		void look_at(const SVec3<>&) noexcept;

		[[nodiscard]] auto look_at_dir() const noexcept -> const SVec3<>&;

		void look_at_dir(const SVec3<>& _dir) noexcept;

		void update(const Input& _input, const float _viewport_x, const float _viewport_y, const float _delta_time);

	private:
		SMat4x4<> view_ = {};
		SMat4x4<> proj_ = {};
		SVec3<> eye_ = {};
		SVec3<> at_ = {};
		SVec3<> forward_ = {};
		SVec3<> left_ = {};
		SVec3<> dir_ = {.0f, .0f, 1.f};
		SVec2<> mouse_prev_ = {};
		SVec2<> mouse_angles_ = {};
		SVec2<> smooth_mouse_angles_ = {};
	};
}
