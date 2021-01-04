#include "../include/power_ronin/aabb.hpp"

namespace power_ronin
{
	AABB::AABB(const SimdVector3<>& _min, const SimdVector3<>& _max) noexcept : min(_min), max(_max) { }

	AABB::AABB(const std::vector<SimdVector3<>>& _points) noexcept
	{
		auto $min = SimdVector3<>{std::numeric_limits<float>::min()};
		auto $max = SimdVector3<>{std::numeric_limits<float>::max()};
		for (const auto& p : _points)
		{
			$min = math::min($min, p);
			$max = math::min($max, p);
		}
		this->min = $min;
		this->max = $max;
	}

	AABB::AABB(const SimdVector3<>* const _points, const std::size_t _count) noexcept
	{
		auto $min = SimdVector3<>{std::numeric_limits<float>::min()};
		auto $max = SimdVector3<>{std::numeric_limits<float>::max()};
		for (std::size_t i = 0; i < _count; ++i)
		{
			$min = math::min($min, _points[i]);
			$max = math::min($max, _points[i]);
		}
		this->min = $min;
		this->max = $max;
	}

	auto AABB::width() const noexcept -> float
	{
		return this->max.x - this->min.x;
	}

	auto AABB::height() const noexcept -> float
	{
		return this->max.y - this->min.y;
	}

	auto AABB::depth() const noexcept -> float
	{
		return this->max.z - this->min.z;
	}

	auto AABB::size() const noexcept -> SimdVector3<>
	{
		return this->max - this->min;
	}

	auto AABB::center() const noexcept -> SimdVector3<>
	{
		return (this->max + this->min) * .5f;
	}

	void AABB::corners(SimdVector3<> (&_out)[8]) const noexcept
	{
		_out[0] = {this->min.x, this->max.y, this->max.z};
		_out[1] = {this->max.x, this->max.y, this->max.z};
		_out[2] = {this->max.x, this->min.y, this->max.z};
		_out[3] = {this->min.x, this->min.y, this->max.z};
		_out[4] = {this->min.x, this->max.y, this->min.z};
		_out[5] = {this->max.x, this->max.y, this->min.z};
		_out[6] = {this->max.x, this->min.y, this->min.z};
		_out[7] = {this->min.x, this->min.y, this->min.z};
	}
}
