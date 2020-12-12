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

#include "../../include/dce/flycam.hpp"
#include "../../include/dce/runtime.hpp"
#include "gui/gui_headers.hpp"

namespace dce {
	auto FlyCam::get_projection_matrix() const noexcept -> const Matrix4x4<>& {
		return this->proj_;
	}

	auto FlyCam::get_view_matrix() const noexcept -> const Matrix4x4<>& {
		return this->view_;
	}

	auto FlyCam::get_eye_vector() const noexcept -> const Vector3<>& {
		return this->eye_;
	}

	auto FlyCam::get_direction_vector() const noexcept -> const Vector3<>& {
		return this->at_;
	}

	void FlyCam::set_position(const Vector3<>& _position) noexcept {
		this->eye_ = _position;
	}

	void FlyCam::update(const Input& _input, const float _viewport_x, const float _viewport_y, const float _delta_time) {
		/*[[unlikely]] if (ImGui::IsAnyItemHovered() || ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
			return;
		}*/
		const auto mouse = _input.get_mouse_position();

		const float speed = this->move_speed;

		[[unlikely]] if (_input.is_mouse_button_down(MouseButton::RIGHT)) {
			auto delta_x = mouse.x - this->mouse_prev_.x;
			auto delta_y = mouse.y - this->mouse_prev_.y;

			delta_x = delta_x * sensitivity;
			delta_y = delta_y * sensitivity;

			this->smooth_mouse_angles_.x = std::lerp(smooth_mouse_angles_.x, delta_x, 1.F / this->smoothness);
			this->smooth_mouse_angles_.y = std::lerp(smooth_mouse_angles_.y, delta_y, 1.F / this->smoothness);

			this->mouse_angles_.x += (delta_x + this->smooth_mouse_angles_.x) * _delta_time;
			this->mouse_angles_.y -= (delta_y + this->smooth_mouse_angles_.y) * _delta_time;

			this->mouse_angles_.y = std::clamp(this->mouse_angles_.y, -this->clamp_y, this->clamp_y);

			const auto dir_x = math::cos(math::radians(this->mouse_angles_.y)) * math::sin(math::radians(this->mouse_angles_.x));
			const auto dir_y = math::sin(math::radians(this->mouse_angles_.y));
			const auto dir_z = math::cos(math::radians(this->mouse_angles_.y)) * math::cos(math::radians(this->mouse_angles_.x));

			this->dir_ = {dir_x, dir_y, dir_z};

			this->mouse_prev_.x = mouse.x;
			this->mouse_prev_.y = mouse.y;
		}
		else {
			this->mouse_prev_.x = mouse.x;
			this->mouse_prev_.y = mouse.y;
		}

		this->forward_ = normalize(this->dir_);
		this->left_ = normalize(cross(this->forward_, math::UP));

		[[likely]] if (_input.is_key_down(Key::W)) {
			this->eye_ += Vector3<>{speed * _delta_time} * this->forward_;
		}

		[[likely]] if (_input.is_key_down(Key::A)) {
			this->eye_ += Vector3<>{speed * _delta_time} * this->left_;
		}

		[[likely]] if (_input.is_key_down(Key::S)) {
			this->eye_ -= Vector3<>{speed * _delta_time} * this->forward_;
		}

		[[likely]] if (_input.is_key_down(Key::D)) {
			this->eye_ -= Vector3<>{speed * _delta_time} * this->left_;
		}

		this->at_ = this->eye_ + dir_;

		this->view_ = lookAtLH(this->eye_, this->at_, math::UP);
		this->proj_ = math::perspectiveFovLH<float>(math::radians(this->fov), _viewport_x, _viewport_y, this->near_clip
		                                            , this->far_clip);
	}
}
