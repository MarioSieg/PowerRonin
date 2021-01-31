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
	/// <summary>
	/// Represents a light.
	/// </summary>
	class Light final
	{
	public:
		/// <summary>
		/// The type of the light.
		/// </summary>
		enum class Type
		{
			Directional,
			Spot,
			Point
		} Type = Type::Directional;

		/// <summary>
		/// The light color.
		/// </summary>
		Color<> Color = {1.f, 1.f, 1.f, 1.f};

		/// <summary>
		/// The light intensity in Lux.
		/// </summary>
		float Intensity = 1.f;
	};
}
