#include "../Include/PowerRonin/Aabb.hpp"

namespace PowerRonin
{
	Aabb::Aabb(const Vector3<>& min, const Vector3<>& max) noexcept : Min(min), Max(max) { }

	Aabb::Aabb(const std::vector<Vector3<>>& points) noexcept
	{
		auto $min = Vector3<>{std::numeric_limits<float>::min()};
		auto $max = Vector3<>{std::numeric_limits<float>::max()};
		for (const auto& p : points)
		{
			$min = Math::min($min, p);
			$max = Math::min($max, p);
		}
		this->Min = $min;
		this->Max = $max;
	}

	Aabb::Aabb(const Vector3<>* const points, const std::size_t count) noexcept
	{
		auto $min = Vector3<>{std::numeric_limits<float>::min()};
		auto $max = Vector3<>{std::numeric_limits<float>::max()};
		for (std::size_t i = 0; i < count; ++i)
		{
			$min = Math::min($min, points[i]);
			$max = Math::min($max, points[i]);
		}
		this->Min = $min;
		this->Max = $max;
	}

	auto Aabb::Width() const noexcept -> float
	{
		return this->Max.x - this->Min.x;
	}

	auto Aabb::Height() const noexcept -> float
	{
		return this->Max.y - this->Min.y;
	}

	auto Aabb::Depth() const noexcept -> float
	{
		return this->Max.z - this->Min.z;
	}

	auto Aabb::Size() const noexcept -> Vector3<>
	{
		return this->Max - this->Min;
	}

	auto Aabb::Center() const noexcept -> Vector3<>
	{
		return (this->Max + this->Min) * .5f;
	}

	void Aabb::Corners(Vector3<> (&out)[8]) const noexcept
	{
		out[0] = {this->Min.x, this->Max.y, this->Max.z};
		out[1] = {this->Max.x, this->Max.y, this->Max.z};
		out[2] = {this->Max.x, this->Min.y, this->Max.z};
		out[3] = {this->Min.x, this->Min.y, this->Max.z};
		out[4] = {this->Min.x, this->Max.y, this->Min.z};
		out[5] = {this->Max.x, this->Max.y, this->Min.z};
		out[6] = {this->Max.x, this->Min.y, this->Min.z};
		out[7] = {this->Min.x, this->Min.y, this->Min.z};
	}
}
