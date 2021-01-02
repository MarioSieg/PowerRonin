#include "../../include/dce/transform.hpp"

namespace dce
{
	auto Transform::calculate_matrix() const noexcept -> SimdMatrix4x4<>
	{
		auto transform = math::identity<SimdMatrix4x4<>>();
		transform = math::scale(transform, this->scale);
		transform *= mat4_cast(this->rotation);
		transform = translate(transform, this->position);
		return transform;
	}


	auto Transform::forward() const noexcept -> SimdVector3<>
	{
		return this->rotation * SimdVector3<>{0, 0, 1};
	}

	auto Transform::back() const noexcept -> SimdVector3<>
	{
		return this->rotation * SimdVector3<>{0, 0, -1};
	}

	auto Transform::up() const noexcept -> SimdVector3<>
	{
		return this->rotation * SimdVector3<>{0, 1, 0};
	}

	auto Transform::down() const noexcept -> SimdVector3<>
	{
		return this->rotation * SimdVector3<>{0, -1, 0};
	}

	auto Transform::left() const noexcept -> SimdVector3<>
	{
		return this->rotation * SimdVector3<>{-1, 0, 0};
	}

	auto Transform::right() const noexcept -> SimdVector3<>
	{
		return this->rotation * SimdVector3<>{1, 0, 0};
	}
}
