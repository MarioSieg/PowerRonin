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

#include "mathtypes.hpp"
#include <cstdint>

namespace power_ronin
{
	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_float = float;
	static_assert(sizeof(CS_float) == 4);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_double = double;
	static_assert(sizeof(CS_double) == 8);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_bool = bool;
	static_assert(sizeof(CS_bool) == 1);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_byte = std::uint8_t;
	static_assert(sizeof(CS_byte) == 1);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_sbyte = std::int8_t;
	static_assert(sizeof(CS_sbyte) == 1);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_short = std::int16_t;
	static_assert(sizeof(CS_short) == 2);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_ushort = std::uint16_t;
	static_assert(sizeof(CS_ushort) == 2);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_int = std::int32_t;
	static_assert(sizeof(CS_int) == 4);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_uint = std::uint32_t;
	static_assert(sizeof(CS_uint) == 4);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_long = std::int64_t;
	static_assert(sizeof(CS_long) == 8);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_ulong = std::uint64_t;
	static_assert(sizeof(CS_ulong) == 8);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	struct CS_Vector2 final
	{
		CS_float x;
		CS_float y;

		explicit inline operator SimdVector2<CS_float>() const noexcept
		{
			return SimdVector2<CS_float>(x, y);
		}
	};

	static_assert(sizeof(CS_Vector2) == sizeof(CS_float) * 2);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	struct CS_Vector3 final
	{
		CS_float x;
		CS_float y;
		CS_float z;


		explicit inline operator SimdVector3<CS_float>() const noexcept
		{
			return SimdVector3<CS_float>(x, y, z);
		}
	};

	static_assert(sizeof(CS_Vector3) == sizeof(CS_float) * 3);

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	struct CS_Vector4 final
	{
		CS_float x;
		CS_float y;
		CS_float z;
		CS_float w;


		explicit inline operator SimdVector4<CS_float>() const noexcept
		{
			return SimdVector4<CS_float>(x, y, z, w);
		}
	};

	static_assert(sizeof(CS_Vector4) == sizeof(CS_float) * 4);

	using CS_Quaternion = CS_Vector4;

	struct CS_Size2 final
	{
		CS_uint width;
		CS_uint height;
	};

	static_assert(sizeof(CS_Size2) == sizeof(CS_uint) * 2);

	using CS_Size2F = CS_Vector2;

#define CS_HYBRID_INTEROP(_name)
}
