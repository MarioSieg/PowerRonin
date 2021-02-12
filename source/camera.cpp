#include "../Include/PowerRonin/Camera.hpp"

namespace PowerRonin
{
	void Camera::Recalculate(const Transform& transform, const Vector2<>& viewportSize, Matrix4x4<>& outView, Matrix4x4<>& outProj) const noexcept
	{
		const Vector3<> up = {.0f, 1.f, .0f};
		outView = Math::lookAtLH(transform.position, transform.position + transform.forward(), up);
		outProj = Math::perspectiveFovLH
		(
			Math::radians(this->Fov),
			static_cast<float>(viewportSize.x),
			static_cast<float>(viewportSize.y),
			this->NearClip,
			this->FarClip
		);
	}
}
