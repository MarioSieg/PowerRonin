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

#include "env.hpp"
#include <cstdint>

namespace power_ronin
{
	constexpr auto uint32_sels(const std::uint32_t _t, const std::uint32_t _x,
	                           const std::uint32_t _b) noexcept -> std::uint32_t
	{
		const std::uint32_t mask = static_cast<int32_t>(_t) >> 31;
		const std::uint32_t sel_a = _x & mask;
		const std::uint32_t sel_b = _b & ~mask;
		const std::uint32_t result = sel_a | sel_b;

		return result;
	}

	template <typename T> requires std::is_trivial<T>::value constexpr auto uint32_cntlz(T x) noexcept -> std::uint32_t;

	template <>
	constexpr auto uint32_cntlz(const uint64_t x) noexcept -> std::uint32_t
	{
		return (x & UINT64_C(0xffffffff00000000)) != 0u
			       ? uint32_cntlz(static_cast<uint32_t>(x >> 32))
			       : uint32_cntlz(static_cast<uint32_t>(x)) + 32;
	}

	template <>
	constexpr auto uint32_cntlz(const std::uint8_t x) noexcept -> std::uint32_t
	{
		return uint32_cntlz<uint32_t>(x) - 24;
	}

	template <>
	constexpr auto uint32_cntlz(const std::int8_t x) noexcept -> std::uint32_t
	{
		return uint32_cntlz<uint8_t>(x);
	}

	template <>
	constexpr auto uint32_cntlz(const std::uint16_t x) noexcept -> std::uint32_t
	{
		return uint32_cntlz<uint32_t>(x) - 16;
	}

	template <>
	constexpr auto uint32_cntlz(const std::int16_t x) noexcept -> std::uint32_t
	{
		return uint32_cntlz<uint16_t>(x);
	}

	template <>
	constexpr auto uint32_cntlz(const std::int32_t x) noexcept -> std::uint32_t
	{
		return uint32_cntlz<uint32_t>(x);
	}

	template <>
	constexpr auto uint32_cntlz(const std::int64_t x) noexcept -> std::uint32_t
	{
		return uint32_cntlz<uint64_t>(x);
	}

	extern auto half_from_float(float x) noexcept -> std::uint16_t;

	extern auto half_to_float(uint16_t x) noexcept -> float;
}

// namespace power_ronin
// namespace power_ronin
