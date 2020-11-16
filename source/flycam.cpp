// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: flycam.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#include "flycam.hpp"
#include "gui/gui_headers.hpp"

namespace dce {

	auto FlyCam::get_projection_matrix() const noexcept -> const Matrix4x4& {
		return this->proj_;
	}

	auto FlyCam::get_view_matrix() const noexcept -> const Matrix4x4& {
		return this->view_;
	}

	auto FlyCam::get_eye_vector() const noexcept -> const Vec3& {
		return this->eye_;
	}

	auto FlyCam::get_direction_vector() const noexcept -> const Vec3& {
		return this->at_;
	}

	auto FlyCam::get_upwards_vector() const noexcept -> const Vec3& {
		return this->up_;
	}

	void FlyCam::set_position(const Vec3 &_position) noexcept {
		this->eye_ = _position;
	}

	void FlyCam::update(const float _delta_time) {
		auto &io = ImGui::GetIO();
		const auto mouse = ImGui::GetMousePos();

		const float speed = io.KeyMods & ImGuiKeyModFlags_Shift ? this->fast_move_speed : this->move_speed;

		[[unlikely]] if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {

			const auto delta_x = mouse.x - this->mouse_prev_.x;
			const auto delta_y = mouse.y - this->mouse_prev_.y;

			this->mouse_angles_.x += delta_x * sensitivity * _delta_time;
			this->mouse_angles_.y -= delta_y * sensitivity * _delta_time;

			Vec3 dir = {
				math::cos(math::radians(this->mouse_angles_.y)) * math::sin(math::radians(this->mouse_angles_.x))
				, math::sin(math::radians(this->mouse_angles_.y))
				, math::cos(math::radians(this->mouse_angles_.y)) * math::cos(math::radians(this->mouse_angles_.x))
			};

			this->mouse_prev_.x = mouse.x;
			this->mouse_prev_.y = mouse.y;

			this->forward_ = normalize(dir);
			this->left_ = normalize(cross(this->forward_, this->up_));
			this->at_ = this->eye_ + dir;
		}
		else {
			mouse_prev_.x = mouse.x;
			mouse_prev_.y = mouse.y;
		}

		[[unlikely]] if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_UpArrow))) {
			this->eye_ += Vec3{speed * _delta_time} * this->forward_;
		}

		[[unlikely]] if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_DownArrow))) {
			this->eye_ -= Vec3{speed * _delta_time} * this->forward_;
		}

		[[unlikely]] if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftArrow))) {
			this->eye_ += Vec3{speed * _delta_time} * this->left_;
		}

		[[unlikely]] if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_RightArrow))) {
			this->eye_ -= Vec3{speed * _delta_time} * this->left_;
		}

		this->view_ = lookAtLH(this->eye_, this->at_, this->up_);
		this->proj_ = math::perspectiveFovLH<float>(math::radians(this->fov), io.DisplaySize.x, io.DisplaySize.y
		                                            , this->near_clip, this->far_clip);
	}
}
