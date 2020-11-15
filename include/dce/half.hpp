// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: half.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 04.11.2020 00:34

#pragma once

#include "env.hpp"
#include <cstdint>

namespace dce {
	constexpr auto uint32_sels(const std::uint32_t _t, const std::uint32_t _x
	                           , const std::uint32_t _b) noexcept -> std::uint32_t {
		const std::uint32_t mask = static_cast<int32_t>(_t) >> 31;
		const std::uint32_t sel_a = _x & mask;
		const std::uint32_t sel_b = _b & ~mask;
		const std::uint32_t result = sel_a | sel_b;

		return result;
	}

	template <typename T> requires std::is_trivial<T>::value constexpr auto uint32_cntlz(T x) noexcept -> std::uint32_t;

	template <>
	constexpr auto uint32_cntlz(const uint64_t x) noexcept -> std::uint32_t {
		return (x & UINT64_C(0xffffffff00000000)) != 0u
			       ? uint32_cntlz(static_cast<uint32_t>(x >> 32))
			       : uint32_cntlz(static_cast<uint32_t>(x)) + 32;
	}

	template <>
	constexpr auto uint32_cntlz(const std::uint8_t x) noexcept -> std::uint32_t {
		return uint32_cntlz<uint32_t>(x) - 24;
	}

	template <>
	constexpr auto uint32_cntlz(const std::int8_t x) noexcept -> std::uint32_t {
		return uint32_cntlz<uint8_t>(x);
	}

	template <>
	constexpr auto uint32_cntlz(const std::uint16_t x) noexcept -> std::uint32_t {
		return uint32_cntlz<uint32_t>(x) - 16;
	}

	template <>
	constexpr auto uint32_cntlz(const std::int16_t x) noexcept -> std::uint32_t {
		return uint32_cntlz<uint16_t>(x);
	}

	template <>
	constexpr auto uint32_cntlz(const std::int32_t x) noexcept -> std::uint32_t {
		return uint32_cntlz<uint32_t>(x);
	}

	template <>
	constexpr auto uint32_cntlz(const std::int64_t x) noexcept -> std::uint32_t {
		return uint32_cntlz<uint64_t>(x);
	}

	extern auto half_from_float(float x) noexcept -> std::uint16_t;

	extern auto half_to_float(uint16_t x) noexcept -> float;
}

// namespace dce
// namespace dce
