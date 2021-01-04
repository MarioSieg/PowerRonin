#pragma once

#include<cstdint>

namespace power_ronin
{
	extern auto to_unorm(float value, float scale) noexcept -> std::uint32_t;

	extern auto from_unorm(std::uint32_t value, float scale) noexcept -> float;

	extern auto to_snorm(float value, float scale) noexcept -> std::int32_t;

	extern auto from_snorm(std::int32_t value, float scale) noexcept -> float;

	// a8
	extern void pack_a8(void* dst, const float* src) noexcept;
	extern void unpack_a8(float* dst, const void* src) noexcept;

	// r8
	extern void pack_r8(void* dst, const float* src) noexcept;
	extern void unpack_r8(float* dst, const void* src) noexcept;

	// r8s
	extern void pack_r8s(void* dst, const float* src) noexcept;
	extern void unpack_r8s(float* dst, const void* src) noexcept;

	// r8i
	extern void pack_r8i(void* dst, const float* src) noexcept;
	extern void unpack_r8i(float* dst, const void* src) noexcept;

	// r8u
	extern void pack_r8u(void* dst, const float* src) noexcept;
	extern void unpack_r8u(float* dst, const void* src) noexcept;

	// rg8
	extern void pack_rg8(void* dst, const float* src) noexcept;
	extern void unpack_rg8(float* dst, const void* src) noexcept;

	// rg8s
	extern void pack_rg8s(void* dst, const float* src) noexcept;
	extern void unpack_rg8s(float* dst, const void* src) noexcept;

	// rg8i
	extern void pack_rg8i(void* dst, const float* src) noexcept;
	extern void unpack_rg8i(float* dst, const void* src) noexcept;

	// rg8u
	extern void pack_rg8u(void* dst, const float* src) noexcept;
	extern void unpack_rg8u(float* dst, const void* src) noexcept;

	// rgb8
	extern void pack_rgb8(void* dst, const float* src) noexcept;
	extern void unpack_rgb8(float* dst, const void* src) noexcept;

	// rgb8s
	extern void pack_rgb8s(void* dst, const float* src) noexcept;
	extern void unpack_rgb8s(float* dst, const void* src) noexcept;

	// rgb8i
	extern void pack_rgb8i(void* dst, const float* src) noexcept;
	extern void unpack_rgb8i(float* dst, const void* src) noexcept;

	// rgb8u
	extern void pack_rgb8u(void* dst, const float* src) noexcept;
	extern void unpack_rgb8u(float* dst, const void* src) noexcept;

	// rgba8
	extern void pack_rgba8(void* dst, const float* src) noexcept;
	extern void unpack_rgba8(float* dst, const void* src) noexcept;

	// bgra8
	extern void pack_bgra8(void* dst, const float* src) noexcept;
	extern void unpack_bgra8(float* dst, const void* src) noexcept;

	// rgba8s
	extern void pack_rgba8s(void* dst, const float* src) noexcept;
	extern void unpack_rgba8s(float* dst, const void* src) noexcept;

	// rgba8i
	extern void pack_rgba8i(void* dst, const float* src) noexcept;
	extern void unpack_rgba8i(float* dst, const void* src) noexcept;

	// rgba8u
	extern void pack_rgba8u(void* dst, const float* src) noexcept;
	extern void unpack_rgba8u(float* dst, const void* src) noexcept;

	// r16
	extern void pack_r16(void* dst, const float* src) noexcept;
	extern void unpack_r16(float* dst, const void* src) noexcept;

	// r16s
	extern void pack_r16s(void* dst, const float* src) noexcept;
	extern void unpack_r16s(float* dst, const void* src) noexcept;

	// r16i
	extern void pack_r16i(void* dst, const float* src) noexcept;
	extern void unpack_r16i(float* dst, const void* src) noexcept;

	// r16u
	extern void pack_r16u(void* dst, const float* src) noexcept;
	extern void unpack_r16u(float* dst, const void* src) noexcept;

	// r16f
	extern void pack_r16f(void* dst, const float* src) noexcept;
	extern void unpack_r16f(float* dst, const void* src) noexcept;

	// rg16
	extern void pack_rg16(void* dst, const float* src) noexcept;
	extern void unpack_rg16(float* dst, const void* src) noexcept;

	// rg16s
	extern void pack_rg16s(void* dst, const float* src) noexcept;
	extern void unpack_rg16s(float* dst, const void* src) noexcept;

	// rg16i
	extern void pack_rg16i(void* dst, const float* src) noexcept;
	extern void unpack_rg16i(float* dst, const void* src) noexcept;

	// rg16u
	extern void pack_rg16u(void* dst, const float* src) noexcept;
	extern void unpack_rg16u(float* dst, const void* src) noexcept;

	// rg16f
	extern void pack_rg16f(void* dst, const float* src) noexcept;
	extern void unpack_rg16f(float* dst, const void* src) noexcept;

	// rgba16
	extern void pack_rgba16(void* dst, const float* src) noexcept;
	extern void unpack_rgba16(float* dst, const void* src) noexcept;

	// rgba16s
	extern void pack_rgba16s(void* dst, const float* src) noexcept;
	extern void unpack_rgba16s(float* dst, const void* src) noexcept;

	// rgba16i
	extern void pack_rgba16i(void* dst, const float* src) noexcept;
	extern void unpack_rgba16i(float* dst, const void* src) noexcept;

	// rgba16u
	extern void pack_rgba16u(void* dst, const float* src) noexcept;
	extern void unpack_rgba16u(float* dst, const void* src) noexcept;

	// rgba16f
	extern void pack_rgba16f(void* dst, const float* src) noexcept;
	extern void unpack_rgba16f(float* dst, const void* src) noexcept;

	// r32i
	extern void pack_r32i(void* dst, const float* src) noexcept;
	extern void unpack_r32i(float* dst, const void* src) noexcept;

	// r32u
	extern void pack_r32u(void* dst, const float* src) noexcept;
	extern void unpack_r32u(float* dst, const void* src) noexcept;

	// r32f
	extern void pack_r32f(void* dst, const float* src) noexcept;
	extern void unpack_r32f(float* dst, const void* src) noexcept;

	// rg32i
	extern void pack_rg32i(void* dst, const float* src) noexcept;
	extern void unpack_rg32i(float* dst, const void* src) noexcept;

	// rg32u
	extern void pack_rg32u(void* dst, const float* src) noexcept;
	extern void unpack_rg32u(float* dst, const void* src) noexcept;

	// rgb9e5f
	extern void pack_rgb9e5f(void* dst, const float* src) noexcept;
	extern void unpack_rgb9e5f(float* dst, const void* src) noexcept;

	// rgba32i
	extern void pack_rgba32i(void* dst, const float* src) noexcept;
	extern void unpack_rgba32i(float* dst, const void* src) noexcept;

	// rgba32u
	extern void pack_rgba32u(void* dst, const float* src) noexcept;
	extern void unpack_rgba32u(float* dst, const void* src) noexcept;

	// rgba32f
	extern void pack_rgba32f(void* dst, const float* src) noexcept;
	extern void unpack_rgba32f(float* dst, const void* src) noexcept;

	// r5g6b5
	extern void pack_r5g6b5(void* dst, const float* src) noexcept;
	extern void unpack_r5g6b5(float* dst, const void* src) noexcept;

	// rgba4
	extern void pack_rgba4(void* dst, const float* src) noexcept;
	extern void unpack_rgba4(float* dst, const void* src) noexcept;

	// rgba4
	extern void pack_bgra4(void* dst, const float* src) noexcept;
	extern void unpack_bgra4(float* dst, const void* src) noexcept;

	// rgb5a1
	extern void pack_rgb5a1(void* dst, const float* src) noexcept;
	extern void unpack_rgb5a1(float* dst, const void* src) noexcept;

	// bgr5a1
	extern void pack_bgr5a1(void* dst, const float* src) noexcept;
	extern void unpack_bgr5a1(float* dst, const void* src) noexcept;

	// rgb10a2
	extern void pack_rgb10a2(void* dst, const float* src) noexcept;
	extern void unpack_rgb10a2(float* dst, const void* src) noexcept;

	// rg11b10f
	extern void pack_rg11b10f(void* dst, const float* src) noexcept;
	extern void unpack_rg11b10f(float* dst, const void* src) noexcept;

	// rg32f
	extern void pack_rg32f(void* dst, const float* src) noexcept;
	extern void unpack_rg32f(float* dst, const void* src) noexcept;
} // namespace power_ronin // namespace power_ronin
