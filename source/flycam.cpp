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

#include "../../include/power_ronin/flycam.hpp"
#include "../../include/power_ronin/runtime.hpp"
#include "gui/gui_headers.hpp"

namespace power_ronin
{
	auto EditorCamera::projection_matrix() const noexcept -> const SimdMatrix4x4<>&
	{
		return this->proj_;
	}

	auto EditorCamera::view_matrix() const noexcept -> const SimdMatrix4x4<>&
	{
		return this->view_;
	}

	auto EditorCamera::position() const noexcept -> const SimdVector3<>&
	{
		return this->eye_;
	}

	auto EditorCamera::look_at() const noexcept -> const SimdVector3<>&
	{
		return this->at_;
	}

	void EditorCamera::look_at(const SimdVector3<>& _at) noexcept
	{
		this->at_ = _at;
	}

	auto EditorCamera::look_at_dir() const noexcept -> const SimdVector3<>&
	{
		return this->dir_;
	}

	void EditorCamera::look_at_dir(const SimdVector3<>& _dir) noexcept
	{
		this->dir_ = _dir;
	}

	void EditorCamera::position(const SimdVector3<>& _position) noexcept
	{
		this->eye_ = _position;
	}

	void EditorCamera::update(const Input& _input, const float _viewport_x, const float _viewport_y,
	                          const float _delta_time)
	{
		/*[[unlikely]] if (ImGui::IsAnyItemHovered() || ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
			return;
		}*/
		auto mouse = _input.mouse_pos();
		const float speed = this->move_speed;

		if (_input.is_mouse_button_down(MouseButton::RIGHT)) [[unlikely]]
		{
			auto delta_x = mouse.x - this->mouse_prev_.x;
			auto delta_y = mouse.y - this->mouse_prev_.y;

			delta_x = delta_x * sensitivity;
			delta_y = delta_y * sensitivity;

			this->smooth_mouse_angles_.x = std::lerp(smooth_mouse_angles_.x, delta_x, 1.F / this->smoothness);
			this->smooth_mouse_angles_.y = std::lerp(smooth_mouse_angles_.y, delta_y, 1.F / this->smoothness);

			this->mouse_angles_.x += delta_x * _delta_time + this->smooth_mouse_angles_.x;
			this->mouse_angles_.y -= delta_y * _delta_time + this->smooth_mouse_angles_.y;

			this->mouse_angles_.y = std::clamp(this->mouse_angles_.y, -this->clamp_y, this->clamp_y);

			const auto dir_x = math::cos(math::radians(this->mouse_angles_.y)) * math::sin(
				math::radians(this->mouse_angles_.x));
			const auto dir_y = math::sin(math::radians(this->mouse_angles_.y));
			const auto dir_z = math::cos(math::radians(this->mouse_angles_.y)) * math::cos(
				math::radians(this->mouse_angles_.x));

			this->dir_ = SimdVector3<>{dir_x, dir_y, dir_z};

			this->mouse_prev_.x = mouse.x;
			this->mouse_prev_.y = mouse.y;
		}
		else
		{
			this->mouse_prev_.x = mouse.x;
			this->mouse_prev_.y = mouse.y;
		}

		this->forward_ = normalize(this->dir_);
		this->left_ = normalize(cross(this->forward_, math::UP));

		if (_input.is_key_down(Key::W)) [[likely]]
		{
			this->eye_ += SimdVector3<>{speed * _delta_time} * this->forward_;
		}

		if (_input.is_key_down(Key::A)) [[likely]]
		{
			this->eye_ += SimdVector3<>{speed * _delta_time} * this->left_;
		}

		if (_input.is_key_down(Key::S)) [[likely]]
		{
			this->eye_ -= SimdVector3<>{speed * _delta_time} * this->forward_;
		}

		if (_input.is_key_down(Key::D)) [[likely]]
		{
			this->eye_ -= SimdVector3<>{speed * _delta_time} * this->left_;
		}

		this->at_ = this->eye_ + dir_;

		this->view_ = lookAtLH(this->eye_, this->at_, math::UP);
		this->proj_ = math::perspectiveFovLH<float>(math::radians(this->fov), _viewport_x, _viewport_y, this->near_clip
		                                            , this->far_clip);
	}
}
