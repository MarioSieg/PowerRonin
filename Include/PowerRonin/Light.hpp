#pragma once

#include "MathLib.hpp"

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
