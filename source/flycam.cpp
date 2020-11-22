// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: flycam.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 18.11.2020 13:48

#include "../../include/dce/flycam.hpp"
#include "../../include/dce/state.hpp"

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

	auto FlyCam::get_upwards_vector() const noexcept -> const Vector3<>& {
		return this->up_;
	}

	void FlyCam::set_position(const Vector3<>& _position) noexcept {
		this->eye_ = _position;
	}

	void FlyCam::update(const State& _state) {
		const auto& input = _state.input();
		const auto mouse = input.get_mouse_position();
		const auto viewport_x = _state.config().display.width;
		const auto viewport_y = _state.config().display.height;
		const auto delta_time = static_cast<float>(_state.chrono().delta_time);

		const float speed = this->move_speed;

		[[unlikely]] if (input.is_mouse_button_down(MouseButton::RIGHT)) {

			const auto delta_x = mouse.x - this->mouse_prev_.x;
			const auto delta_y = mouse.y - this->mouse_prev_.y;

			this->mouse_angles_.x += delta_x * sensitivity * delta_time;
			this->mouse_angles_.y -= delta_y * sensitivity * delta_time;

			this->dir_ = {math::cos(math::radians(this->mouse_angles_.y)) * math::sin(math::radians(this->mouse_angles_.x)), math::sin(math::radians(this->mouse_angles_.y)), math::cos(math::radians(this->mouse_angles_.y)) * math::cos(math::radians(this->mouse_angles_.x))};

			this->mouse_prev_.x = mouse.x;
			this->mouse_prev_.y = mouse.y;

		}
		else {
			mouse_prev_.x = mouse.x;
			mouse_prev_.y = mouse.y;
		}

		this->forward_ = normalize(this->dir_);
		this->left_ = normalize(cross(this->forward_, this->up_));
		this->at_ = this->eye_ + dir_;

		[[unlikely]] if (input.is_key_down(Key::W)) {
			this->eye_ += Vector3<>{speed * delta_time} * this->forward_;
		}

		[[unlikely]] if (input.is_key_down(Key::A)) {
			this->eye_ += Vector3<>{speed * delta_time} * this->left_;
		}

		[[unlikely]] if (input.is_key_down(Key::S)) {
			this->eye_ -= Vector3<>{speed * delta_time} * this->forward_;
		}

		[[unlikely]] if (input.is_key_down(Key::D)) {
			this->eye_ -= Vector3<>{speed * delta_time} * this->left_;
		}

		this->view_ = lookAtLH(this->eye_, this->at_, this->up_);
		this->proj_ = math::perspectiveFovLH<float>(math::radians(this->fov), viewport_x, viewport_y, this->near_clip, this->far_clip);
	}
}
