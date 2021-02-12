#pragma once

#include "MathLib.hpp"

namespace PowerRonin
{
	/* Represents a physical collider. */
	class Collider final
	{
	public:
		union ColliderData
		{
			/* Box collider data. */
			struct
			{
				Vector3<> HalfExtents;
			} Box = {};

			/* Sphere collider data. */
			struct
			{
				float Radius = 10.f;
			} Sphere;
		} Data = {.Box = {.HalfExtents = {20.f, 20.f, 20.f}}};

		/* Discriminator */
		enum class Type : std::uint8_t
		{
			Box,
			Sphere
		} Type = Type::Box;
	};
}
