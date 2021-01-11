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

namespace power_ronin
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
				SVec3<> half_extents;
			} box = {};

			/* Sphere collider data. */
			struct
			{
				float radius = 10.f;
			} sphere;
		} data = {.box = {.half_extents = {20.f, 20.f, 20.f}}};

		/* Discriminator */
		enum class Type : std::uint8_t
		{
			BOX,
			SPHERE
		} type = Type::BOX;
	};
}
