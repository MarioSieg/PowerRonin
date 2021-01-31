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

namespace PowerRonin
{
	auto EditorCamera::ProjectionMatrix() const noexcept -> const Matrix4x4<>&
	{
		return this->proj;
	}

	auto EditorCamera::ViewMatrix() const noexcept -> const Matrix4x4<>&
	{
		return this->view;
	}

	auto EditorCamera::Position() const noexcept -> const Vector3<>&
	{
		return this->eye;
	}

	auto EditorCamera::LookAt() const noexcept -> const Vector3<>&
	{
		return this->at;
	}

	void EditorCamera::LookAt(const Vector3<>& _at) noexcept
	{
		this->at = _at;
	}

	auto EditorCamera::LookAtDir() const noexcept -> const Vector3<>&
	{
		return this->dir;
	}

	void EditorCamera::LookAtDir(const Vector3<>& dir) noexcept
	{
		this->dir = dir;
	}

	void EditorCamera::Position(const Vector3<>& position) noexcept
	{
		this->eye = position;
	}

	void EditorCamera::Update(const Input& input, const float viewportX, const float viewportY,
	                          const float deltaTime)
	{
		/*[[unlikely]] if (ImGui::IsAnyItemHovered() || ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
			return;
		}*/
		auto mouse = input.MousePosition();
		const float speed = this->MoveSpeed;

		if (input.IsMouseButtonDown(MouseButton::Right)) [[unlikely]]
		{
			auto delta_x = mouse.x - this->mousePrev.x;
			auto delta_y = mouse.y - this->mousePrev.y;

			delta_x = delta_x * Sensitivity;
			delta_y = delta_y * Sensitivity;

			this->smoothMouseAngles.x = std::lerp(smoothMouseAngles.x, delta_x, 1.F / this->Smoothness);
			this->smoothMouseAngles.y = std::lerp(smoothMouseAngles.y, delta_y, 1.F / this->Smoothness);

			this->mouseAngles.x += delta_x * deltaTime + this->smoothMouseAngles.x;
			this->mouseAngles.y -= delta_y * deltaTime + this->smoothMouseAngles.y;

			this->mouseAngles.y = std::clamp(this->mouseAngles.y, -this->ClampY, this->ClampY);

			const auto dir_x = Math::cos(Math::radians(this->mouseAngles.y)) * Math::sin(
				Math::radians(this->mouseAngles.x));
			const auto dir_y = Math::sin(Math::radians(this->mouseAngles.y));
			const auto dir_z = Math::cos(Math::radians(this->mouseAngles.y)) * Math::cos(
				Math::radians(this->mouseAngles.x));

			this->dir = Vector3<>{dir_x, dir_y, dir_z};

			this->mousePrev.x = mouse.x;
			this->mousePrev.y = mouse.y;
		}
		else
		{
			this->mousePrev.x = mouse.x;
			this->mousePrev.y = mouse.y;
		}

		this->forward = normalize(this->dir);
		this->left = normalize(cross(this->forward, {.0f, 1.f, .0f}));

		if (input.IsKeyDown(Key::W)) [[likely]]
		{
			this->eye += Vector3<>{speed * deltaTime} * this->forward;
		}

		if (input.IsKeyDown(Key::A)) [[likely]]
		{
			this->eye += Vector3<>{speed * deltaTime} * this->left;
		}

		if (input.IsKeyDown(Key::S)) [[likely]]
		{
			this->eye -= Vector3<>{speed * deltaTime} * this->forward;
		}

		if (input.IsKeyDown(Key::D)) [[likely]]
		{
			this->eye -= Vector3<>{speed * deltaTime} * this->left;
		}

		this->at = this->eye + dir;

		this->view = lookAtLH(this->eye, this->at, {.0f, 1.f, .0f});
		this->proj = Math::perspectiveFovLH<float>(Math::radians(this->Fov), viewportX, viewportY, this->NearClip
		                                            , this->FarClip);
	}
}
