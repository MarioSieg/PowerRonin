#pragma once

#include "aabb.hpp"

namespace dce {
	/// <summary>
	/// Represents a view frustum (camera pyramid)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <typename T = float> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	struct Frustum final {
		enum Planes {
			LEFT = 0,
			RIGHT,
			BOTTOM,
			TOP,
			NEAR,
			FAR,
			COUNT,
			COMBO = COUNT * (COUNT - 1) / 2
		};
		
		constexpr Frustum() noexcept = default;
		constexpr Frustum(const Frustum&) noexcept = default;
		constexpr Frustum(Frustum&&) noexcept = default;
		constexpr auto operator=(const Frustum&) noexcept ->Frustum & = default;
		constexpr auto operator=(Frustum&&) noexcept -> Frustum & = default;
		~Frustum() = default;

		[[nodiscard]]
		auto planes() const noexcept -> const SimdVector4<T>(&)[COUNT];

		[[nodiscard]]
		auto points() const noexcept -> const SimdVector3<T>(&)[8];

		void from_camera_matrix(const SimdMatrix4x4<T>& _view_proj) noexcept;

		[[nodiscard]]
		auto is_aabb_visible(const AABB<T>& _in) const noexcept -> bool;

	private:
		template<Planes I, Planes J>
		struct IJ2K {
			enum { K = I * (9 - I) / 2 + J - 1 };
		};
		SimdVector4<T> planes_[COUNT] = {};
		SimdVector3<T> points_[8] = {};
		template<Planes A, Planes B, Planes C>
		[[nodiscard]] auto intersection(const SimdVector3<T>* const _crosses) const noexcept -> SimdVector3<T> {
			const float D = math::dot(SimdVector3<>(this->planes_[A]), _crosses[IJ2K<B, C>::K]);
			SimdVector3<T> res = glm::mat3(_crosses[IJ2K<B, C>::K], -_crosses[IJ2K<A, C>::K], _crosses[IJ2K<A, B>::K])
				* SimdVector3<>(this->planes_[A].w, this->planes_[B].w, this->planes_[C].w);
			return res * (-1.0f / D);
		}
	};

	template <typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	inline auto Frustum<T>::planes() const noexcept -> const SimdVector4<T>(&)[COUNT]{
		return this->planes_;
	}

	template <typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	inline auto Frustum<T>::points() const noexcept -> const SimdVector3<T>(&)[8]{
		return this->points_;
	}

	template <typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	inline void Frustum<T>::from_camera_matrix(const SimdMatrix4x4<T>& _view_proj) noexcept {
		auto matrix = math::transpose(_view_proj);
		this->planes_[LEFT] = matrix[3] + matrix[0];
		this->planes_[RIGHT] = matrix[3] - matrix[0];
		this->planes_[BOTTOM] = matrix[3] + matrix[1];
		this->planes_[TOP] = matrix[3] - matrix[1];
		this->planes_[NEAR] = matrix[3] + matrix[2];
		this->planes_[FAR] = matrix[3] - matrix[2];

		SimdVector3<T> crosses[COMBO] = {
			math::cross(SimdVector3<T>(this->planes_[LEFT]),   SimdVector3<T>(this->planes_[RIGHT])),
			math::cross(SimdVector3<T>(this->planes_[LEFT]),   SimdVector3<T>(this->planes_[BOTTOM])),
			math::cross(SimdVector3<T>(this->planes_[LEFT]),   SimdVector3<T>(this->planes_[TOP])),
			math::cross(SimdVector3<T>(this->planes_[LEFT]),   SimdVector3<T>(this->planes_[NEAR])),
			math::cross(SimdVector3<T>(this->planes_[LEFT]),   SimdVector3<T>(this->planes_[FAR])),
			math::cross(SimdVector3<T>(this->planes_[RIGHT]),  SimdVector3<T>(this->planes_[BOTTOM])),
			math::cross(SimdVector3<T>(this->planes_[RIGHT]),  SimdVector3<T>(this->planes_[TOP])),
			math::cross(SimdVector3<T>(this->planes_[RIGHT]),  SimdVector3<T>(this->planes_[NEAR])),
			math::cross(SimdVector3<T>(this->planes_[RIGHT]),  SimdVector3<T>(this->planes_[FAR])),
			math::cross(SimdVector3<T>(this->planes_[BOTTOM]), SimdVector3<T>(this->planes_[TOP])),
			math::cross(SimdVector3<T>(this->planes_[BOTTOM]), SimdVector3<T>(this->planes_[NEAR])),
			math::cross(SimdVector3<T>(this->planes_[BOTTOM]), SimdVector3<T>(this->planes_[FAR])),
			math::cross(SimdVector3<T>(this->planes_[TOP]),    SimdVector3<T>(this->planes_[NEAR])),
			math::cross(SimdVector3<T>(this->planes_[TOP]),    SimdVector3<T>(this->planes_[FAR])),
			math::cross(SimdVector3<T>(this->planes_[NEAR]),   SimdVector3<T>(this->planes_[FAR]))
		};

		this->points_[0] = this->intersection<LEFT, BOTTOM, NEAR>(crosses);
		this->points_[1] = this->intersection<LEFT, TOP, NEAR>(crosses);
		this->points_[2] = this->intersection<RIGHT, BOTTOM, NEAR>(crosses);
		this->points_[3] = this->intersection<RIGHT, TOP, NEAR>(crosses);
		this->points_[4] = this->intersection<LEFT, BOTTOM, FAR>(crosses);
		this->points_[5] = this->intersection<LEFT, TOP, FAR>(crosses);
		this->points_[6] = this->intersection<RIGHT, BOTTOM, FAR>(crosses);
		this->points_[7] = this->intersection<RIGHT, TOP, FAR>(crosses);
	}


	template <typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
	inline auto Frustum<T>::is_aabb_visible(const AABB<T>& _in) const noexcept -> bool {
		const auto& minp = _in.min;
		const auto& maxp = _in.max;
		
		for(auto i = 0; i < COUNT; ++i) {
			[[likely]]
			if ((math::dot(this->planes_[i], SimdVector4<T>(minp.x, minp.y, minp.z, 1.0f)) < .0F) &&
				(math::dot(this->planes_[i], SimdVector4<T>(maxp.x, minp.y, minp.z, 1.0f)) < .0F) &&
				(math::dot(this->planes_[i], SimdVector4<T>(minp.x, maxp.y, minp.z, 1.0f)) < .0F) &&
				(math::dot(this->planes_[i], SimdVector4<T>(maxp.x, maxp.y, minp.z, 1.0f)) < .0F) &&
				(math::dot(this->planes_[i], SimdVector4<T>(minp.x, minp.y, maxp.z, 1.0f)) < .0F) &&
				(math::dot(this->planes_[i], SimdVector4<T>(maxp.x, minp.y, maxp.z, 1.0f)) < .0F) &&
				(math::dot(this->planes_[i], SimdVector4<T>(minp.x, maxp.y, maxp.z, 1.0f)) < .0F) &&
				(math::dot(this->planes_[i], SimdVector4<T>(maxp.x, maxp.y, maxp.z, 1.0f)) < .0F)) {
				return false;
			}
		}

		int out;
		out = 0; for (int i = 0; i < 8; i++) out += ((this->points_[i].x > maxp.x) ? 1 : 0); [[likely]] if (out == 8) return false;
		out = 0; for (int i = 0; i < 8; i++) out += ((this->points_[i].x < minp.x) ? 1 : 0); [[likely]] if (out == 8) return false;
		out = 0; for (int i = 0; i < 8; i++) out += ((this->points_[i].y > maxp.y) ? 1 : 0); [[likely]] if (out == 8) return false;
		out = 0; for (int i = 0; i < 8; i++) out += ((this->points_[i].y < minp.y) ? 1 : 0); [[likely]] if (out == 8) return false;
		out = 0; for (int i = 0; i < 8; i++) out += ((this->points_[i].z > maxp.z) ? 1 : 0); [[likely]] if (out == 8) return false;
		out = 0; for (int i = 0; i < 8; i++) out += ((this->points_[i].z < minp.z) ? 1 : 0); [[likely]] if (out == 8) return false;

		return true;
	}
}
