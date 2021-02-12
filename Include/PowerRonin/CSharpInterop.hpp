#pragma once

#include "MathTypes.hpp"
#include <cstdint>

namespace PowerRonin::CSharp
{
	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using $float = float;
	static_assert(sizeof($float) == 4);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using $double = double;
	static_assert(sizeof($double) == 8);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using $bool = bool;
	static_assert(sizeof($bool) == 1);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using $byte = std::uint8_t;
	static_assert(sizeof($byte) == 1);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using $sbyte = std::int8_t;
	static_assert(sizeof($sbyte) == 1);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using $short = std::int16_t;
	static_assert(sizeof($short) == 2);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using $ushort = std::uint16_t;
	static_assert(sizeof($ushort) == 2);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using $int = std::int32_t;
	static_assert(sizeof($int) == 4);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using $uint = std::uint32_t;
	static_assert(sizeof($uint) == 4);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using $long = std::int64_t;
	static_assert(sizeof($long) == 8);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using $ulong = std::uint64_t;
	static_assert(sizeof($ulong) == 8);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	struct $Vector2 final
	{
		$float X;
		$float Y;

		explicit inline operator Vector2<$float>() const noexcept
		{
			return Vector2<$float>(X, Y);
		}
	};

	static_assert(sizeof($Vector2) == sizeof($float) * 2);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	struct $Vector3 final
	{
		$float X;
		$float Y;
		$float Z;


		explicit inline operator Vector3<$float>() const noexcept
		{
			return Vector3<$float>(X, Y, Z);
		}
	};

	static_assert(sizeof($Vector3) == sizeof($float) * 3);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	struct $Vector4 final
	{
		$float X;
		$float Y;
		$float Z;
		$float W;

		explicit inline operator Vector4<$float>() const noexcept
		{
			return Vector4<$float>(X, Y, Z, W);
		}
	};

	static_assert(sizeof($Vector4) == sizeof($float) * 4);

	using $Quaternion = $Vector4;

	struct $Size2 final
	{
		$uint Width;
		$uint Height;
	};

	static_assert(sizeof($Size2) == sizeof($uint) * 2);

	using $Size2F = $Vector2;

#define CSHARP_HYBRID_INTEROP(_name)
}
