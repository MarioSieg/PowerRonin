#pragma once

#include "Transform.hpp"

namespace PowerRonin
{
	/// <summary>
	/// A Camera component.
	/// </summary>
	class Camera final
	{
	public:
		float Fov = 80.F;
		float NearClip = 0.01F;
		float FarClip = 1000.F;

		void Recalculate(const Transform& transform, const Vector2<>& viewportSize, Matrix4x4<>& outView, Matrix4x4<>& outProj) const noexcept;
	};
}
