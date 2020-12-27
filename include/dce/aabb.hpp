#pragma once

#include "mathtypes.hpp"
#include <vector>

namespace dce {
	/// <summary>
	/// Represents an axis aligned bounding box.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	struct AABB final {
		constexpr AABB() noexcept = default;
		constexpr AABB(const SimdVector3<T>& _min, const SimdVector3<T>& _max) noexcept;
		constexpr explicit AABB(const std::vector<SimdVector3<T>>& _points) noexcept;
		constexpr explicit AABB(const SimdVector3<T>* const _points, const std::size_t _count) noexcept;
		constexpr AABB(const AABB&) noexcept = default;
		constexpr AABB(AABB&&) noexcept = default;
		constexpr auto operator=(const AABB&) noexcept -> AABB& = default;
		constexpr auto operator=(AABB&&) noexcept -> AABB& = default;
		~AABB() = default;
		
		SimdVector3<T> min = {};
		SimdVector3<T> max = {};

		[[nodiscard]]
		auto width() const noexcept -> T;

		[[nodiscard]]
		auto height() const noexcept -> T;

		[[nodiscard]]
		auto depth() const noexcept -> T;

		[[nodiscard]]
		auto size() const noexcept -> SimdVector3<T>;

		[[nodiscard]]
		auto center() const noexcept -> SimdVector3<T>;
 
		void corners(SimdVector3<T>(&_out)[8]) const noexcept;
	};

	template <typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	constexpr AABB<T>::AABB(const SimdVector3<T>& _min, const SimdVector3<T>& _max) noexcept : min(_min), max(_max) {
		
	}

	template <typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	constexpr AABB<T>::AABB(const std::vector<SimdVector3<T>>& _points) noexcept {
		auto $min = SimdVector3<T>{ std::numeric_limits<float>::min() };
		auto $max = SimdVector3<T>{ std::numeric_limits<float>::max() };
		for(const auto& p : _points) {
			$min = math::min($min, p);
			$max = math::min($max, p);
		}
		this->min = $min;
		this->max = $max;
	}

	template <typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	constexpr AABB<T>::AABB(const SimdVector3<T>* const _points, const std::size_t _count) noexcept {
		auto $min = SimdVector3<T>{ std::numeric_limits<float>::min() };
		auto $max = SimdVector3<T>{ std::numeric_limits<float>::max() };
		for(std::size_t i = 0; i < _count; ++i) {
			$min = math::min($min, _points[i]);
			$max = math::min($max, _points[i]);
		}
		this->min = $min;
		this->max = $max;
	}

	template <typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	inline auto AABB<T>::width() const noexcept -> T {
		return this->max.x - this->min.x;
	}

	template <typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	inline auto AABB<T>::height() const noexcept -> T {
		return this->max.y - this->min.y;
	}

	template <typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	inline auto AABB<T>::depth() const noexcept -> T {
		return this->max.z - this->min.z;
	}

	template <typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	inline auto AABB<T>::size() const noexcept -> SimdVector3<T> {
		return this->max - this->min;
	}

	template <typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	inline auto AABB<T>::center() const noexcept -> SimdVector3<T> {
		return (this->max + this->min) * .5f;
	}

	template <typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	inline void AABB<T>::corners(SimdVector3<T>(& _out)[8]) const noexcept {
		_out[0] = { this->min.x, this->max.y, this->max.z };
		_out[1] = { this->max.x, this->max.y, this->max.z };
		_out[2] = { this->max.x, this->min.y, this->max.z };
		_out[3] = { this->min.x, this->min.y, this->max.z };
		_out[4] = { this->min.x, this->max.y, this->min.z };
		_out[5] = { this->max.x, this->max.y, this->min.z };
		_out[6] = { this->max.x, this->min.y, this->min.z };
		_out[7] = { this->min.x, this->min.y, this->min.z };
	}
}
