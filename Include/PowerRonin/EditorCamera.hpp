#pragma once

#include "MathLib.hpp"

namespace PowerRonin
{
	class Input;

	/// <summary>
	/// Helper class for a flying editor camera.
	/// </summary>
	class EditorCamera final
	{
	public:
		float MoveSpeed = 8.F;
		float Sensitivity = 0.5F;
		float Fov = 80.F;
		float NearClip = 0.01F;
		float FarClip = 1000.F;
		float Smoothness = 1.F;
		float ClampY = 80.F;

		[[nodiscard]] auto ProjectionMatrix() const noexcept -> const Matrix4x4<>&;

		[[nodiscard]] auto ViewMatrix() const noexcept -> const Matrix4x4<>&;

		[[nodiscard]] auto Position() const noexcept -> const Vector3<>&;

		void Position(const Vector3<>& position) noexcept;

		[[nodiscard]] auto LookAt() const noexcept -> const Vector3<>&;

		void LookAt(const Vector3<>&) noexcept;

		[[nodiscard]] auto LookAtDir() const noexcept -> const Vector3<>&;

		void LookAtDir(const Vector3<>& dir) noexcept;

		void Update(const Input& input, const float viewportX, const float viewportY, const float deltaTime);

	private:
		Matrix4x4<> view = {};
		Matrix4x4<> proj = {};
		Vector3<> eye = {};
		Vector3<> at = {};
		Vector3<> forward = {};
		Vector3<> left = {};
		Vector3<> dir = {.0f, .0f, 1.f};
		Vector2<> mousePrev = {};
		Vector2<> mouseAngles = {};
		Vector2<> smoothMouseAngles = {};
	};
}
