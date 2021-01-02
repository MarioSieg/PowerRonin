#pragma once

#include <cstddef>
#include <cstdint>

namespace dce
{
	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_float = float;

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_double = double;

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_bool = bool;

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_byte = std::uint8_t;

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_sbyte = std::int8_t;

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_short = std::int16_t;

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_ushort = std::uint16_t;

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_int = std::int32_t;

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_uint = std::uint32_t;

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_long = std::int64_t;

	/// <summary>
	/// Maps to C# type.
	/// </summary>
	using CS_ulong = std::uint64_t;

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

#define CS_HYBRID_INTEROP(_name)
}
