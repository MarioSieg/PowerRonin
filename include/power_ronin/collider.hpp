// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#pragma once

#include "mathlib.hpp"

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
