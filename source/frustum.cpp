#include "../Include/PowerRonin/Frustum.hpp"

namespace PowerRonin
{
	template <enum Frustum::Planes I, enum Frustum::Planes J>
	struct IJ2K
	{
		enum { K = I * (9 - I) / 2 + J - 1 };
	};

	template <enum Frustum::Planes A, enum Frustum::Planes B, enum Frustum::Planes C>
	[[nodiscard]] static auto intersection(const Frustum& _frustum,
	                                       const Vector3<>* const _crosses) noexcept -> Vector3<>
	{
		const auto& planes = _frustum.Planes();
		const auto D = Math::dot(Vector3<>(planes[A]), _crosses[IJ2K<B, C>::K]);
		Vector3<> res = glm::mat3(_crosses[IJ2K<B, C>::K], -_crosses[IJ2K<A, C>::K], _crosses[IJ2K<A, B>::K])
			* Vector3<>(planes[A].w, planes[B].w, planes[C].w);
		return res * (-1.0f / D);
	}

	auto Frustum::Planes() const noexcept -> const Vector4<>(&)[Count]
	{
		return this->planes;
	}

	auto Frustum::Points() const noexcept -> const Vector3<>(&)[8]
	{
		return this->points;
	}

	void Frustum::FromCameraMatrix(const Matrix4x4<>& viewProj) noexcept
	{
		auto matrix = Math::transpose(viewProj);
		this->planes[Left] = matrix[3] + matrix[0];
		this->planes[Right] = matrix[3] - matrix[0];
		this->planes[Bottom] = matrix[3] + matrix[1];
		this->planes[Top] = matrix[3] - matrix[1];
		this->planes[Near] = matrix[3] + matrix[2];
		this->planes[Far] = matrix[3] - matrix[2];

		Vector3<> crosses[Combo] = {
			Math::cross(Vector3<>(this->planes[Left]), Vector3<>(this->planes[Right])),
			Math::cross(Vector3<>(this->planes[Left]), Vector3<>(this->planes[Bottom])),
			Math::cross(Vector3<>(this->planes[Left]), Vector3<>(this->planes[Top])),
			Math::cross(Vector3<>(this->planes[Left]), Vector3<>(this->planes[Near])),
			Math::cross(Vector3<>(this->planes[Left]), Vector3<>(this->planes[Far])),
			Math::cross(Vector3<>(this->planes[Right]), Vector3<>(this->planes[Bottom])),
			Math::cross(Vector3<>(this->planes[Right]), Vector3<>(this->planes[Top])),
			Math::cross(Vector3<>(this->planes[Right]), Vector3<>(this->planes[Near])),
			Math::cross(Vector3<>(this->planes[Right]), Vector3<>(this->planes[Far])),
			Math::cross(Vector3<>(this->planes[Bottom]), Vector3<>(this->planes[Top])),
			Math::cross(Vector3<>(this->planes[Bottom]), Vector3<>(this->planes[Near])),
			Math::cross(Vector3<>(this->planes[Bottom]), Vector3<>(this->planes[Far])),
			Math::cross(Vector3<>(this->planes[Top]), Vector3<>(this->planes[Near])),
			Math::cross(Vector3<>(this->planes[Top]), Vector3<>(this->planes[Far])),
			Math::cross(Vector3<>(this->planes[Near]), Vector3<>(this->planes[Far]))
		};

		this->points[0] = intersection<Left, Bottom, Near>(*this, crosses);
		this->points[1] = intersection<Left, Top, Near>(*this, crosses);
		this->points[2] = intersection<Right, Bottom, Near>(*this, crosses);
		this->points[3] = intersection<Right, Top, Near>(*this, crosses);
		this->points[4] = intersection<Left, Bottom, Far>(*this, crosses);
		this->points[5] = intersection<Left, Top, Far>(*this, crosses);
		this->points[6] = intersection<Right, Bottom, Far>(*this, crosses);
		this->points[7] = intersection<Right, Top, Far>(*this, crosses);
	}

	auto Frustum::IsAabbVisible(const Aabb& in) const noexcept -> bool
	{
		const auto& minp = in.Min;
		const auto& maxp = in.Max;

		if (Math::dot(this->planes[0], Vector4<>(minp.x, minp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[0], Vector4<>(maxp.x, minp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[0], Vector4<>(minp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[0], Vector4<>(maxp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[0], Vector4<>(minp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[0], Vector4<>(maxp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[0], Vector4<>(minp.x, maxp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[0], Vector4<>(maxp.x, maxp.y, maxp.z, 1.0f)) < .0F) [[likely]]
		{
			return false;
		}

		if (Math::dot(this->planes[1], Vector4<>(minp.x, minp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[1], Vector4<>(maxp.x, minp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[1], Vector4<>(minp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[1], Vector4<>(maxp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[1], Vector4<>(minp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[1], Vector4<>(maxp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[1], Vector4<>(minp.x, maxp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[1], Vector4<>(maxp.x, maxp.y, maxp.z, 1.0f)) < .0F) [[likely]]
		{
			return false;
		}

		if (Math::dot(this->planes[2], Vector4<>(minp.x, minp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[2], Vector4<>(maxp.x, minp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[2], Vector4<>(minp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[2], Vector4<>(maxp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[2], Vector4<>(minp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[2], Vector4<>(maxp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[2], Vector4<>(minp.x, maxp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[2], Vector4<>(maxp.x, maxp.y, maxp.z, 1.0f)) < .0F) [[likely]]
		{
			return false;
		}

		if (Math::dot(this->planes[3], Vector4<>(minp.x, minp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[3], Vector4<>(maxp.x, minp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[3], Vector4<>(minp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[3], Vector4<>(maxp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[3], Vector4<>(minp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[3], Vector4<>(maxp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[3], Vector4<>(minp.x, maxp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[3], Vector4<>(maxp.x, maxp.y, maxp.z, 1.0f)) < .0F) [[likely]]
		{
			return false;
		}

		if (Math::dot(this->planes[4], Vector4<>(minp.x, minp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[4], Vector4<>(maxp.x, minp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[4], Vector4<>(minp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[4], Vector4<>(maxp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[4], Vector4<>(minp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[4], Vector4<>(maxp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[4], Vector4<>(minp.x, maxp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[4], Vector4<>(maxp.x, maxp.y, maxp.z, 1.0f)) < .0F) [[likely]]
		{
			return false;
		}

		if (Math::dot(this->planes[5], Vector4<>(minp.x, minp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[5], Vector4<>(maxp.x, minp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[5], Vector4<>(minp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[5], Vector4<>(maxp.x, maxp.y, minp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[5], Vector4<>(minp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[5], Vector4<>(maxp.x, minp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[5], Vector4<>(minp.x, maxp.y, maxp.z, 1.0f)) < .0F &&
			Math::dot(this->planes[5], Vector4<>(maxp.x, maxp.y, maxp.z, 1.0f)) < .0F) [[likely]]
		{
			return false;
		}

		std::int_fast32_t out = 0;

		out += this->points[0].x > maxp.x;
		out += this->points[1].x > maxp.x;
		out += this->points[2].x > maxp.x;
		out += this->points[3].x > maxp.x;
		out += this->points[4].x > maxp.x;
		out += this->points[5].x > maxp.x;
		out += this->points[6].x > maxp.x;
		out += this->points[7].x > maxp.x;

		if (out == 8) [[likely]]
		{
			return false;
		}

		out = 0;

		out += this->points[0].x < minp.x;
		out += this->points[1].x < minp.x;
		out += this->points[2].x < minp.x;
		out += this->points[3].x < minp.x;
		out += this->points[4].x < minp.x;
		out += this->points[5].x < minp.x;
		out += this->points[6].x < minp.x;
		out += this->points[7].x < minp.x;

		if (out == 8) [[likely]]
		{
			return false;
		}

		out = 0;

		out += this->points[0].y > maxp.y;
		out += this->points[1].y > maxp.y;
		out += this->points[2].y > maxp.y;
		out += this->points[3].y > maxp.y;
		out += this->points[4].y > maxp.y;
		out += this->points[5].y > maxp.y;
		out += this->points[6].y > maxp.y;
		out += this->points[7].y > maxp.y;

		if (out == 8) [[likely]]
		{
			return false;
		}

		out = 0;

		out += this->points[0].y < minp.y;
		out += this->points[1].y < minp.y;
		out += this->points[2].y < minp.y;
		out += this->points[3].y < minp.y;
		out += this->points[4].y < minp.y;
		out += this->points[5].y < minp.y;
		out += this->points[6].y < minp.y;
		out += this->points[7].y < minp.y;

		if (out == 8) [[likely]]
		{
			return false;
		}

		out = 0;

		out += this->points[0].z > maxp.z;
		out += this->points[1].z > maxp.z;
		out += this->points[2].z > maxp.z;
		out += this->points[3].z > maxp.z;
		out += this->points[4].z > maxp.z;
		out += this->points[5].z > maxp.z;
		out += this->points[6].z > maxp.z;
		out += this->points[7].z > maxp.z;

		if (out == 8) [[likely]]
		{
			return false;
		}

		out = 0;

		out += this->points[0].z < minp.z;
		out += this->points[1].z < minp.z;
		out += this->points[2].z < minp.z;
		out += this->points[3].z < minp.z;
		out += this->points[4].z < minp.z;
		out += this->points[5].z < minp.z;
		out += this->points[6].z < minp.z;
		out += this->points[7].z < minp.z;

		if (out == 8) [[likely]]
		{
			return false;
		}

		return true;
	}
}
