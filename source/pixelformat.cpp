#include "../include/dce/pixelformat.hpp"
#include "../include/dce/half.hpp"

#include <algorithm>
#include <cmath>
#include <memory>

namespace dce
{
	auto to_unorm(float _value, float _scale) noexcept -> std::uint32_t
	{
		return static_cast<std::uint32_t>(std::round(std::clamp(_value, 0.0F, 1.0F) * _scale));
	}

	auto from_unorm(std::uint32_t _value, float _scale) noexcept -> float
	{
		return static_cast<float>(_value) / _scale;
	}

	auto to_snorm(float _value, float _scale) noexcept -> std::int32_t
	{
		return static_cast<std::int32_t>(std::round(std::clamp(_value, -1.0F, 1.0F) * _scale));
	}

	auto from_snorm(std::int32_t _value, float _scale) noexcept -> float
	{
		return std::max(-1.0F, static_cast<float>(_value) / _scale);
	}

	// a8
	void pack_a8(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint8_t*>(dst1);
		dst[0] = static_cast<std::uint8_t>(to_unorm(src1[3], 255.0F));
	}

	void unpack_a8(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint8_t*>(src1);
		const float aa = from_unorm(src[0], 255.0F);
		dst1[0] = aa;
		dst1[1] = aa;
		dst1[2] = aa;
		dst1[3] = aa;
	}

	// r8
	void pack_r8(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint8_t*>(dst1);
		dst[0] = static_cast<std::uint8_t>(to_unorm(src1[0], 255.0F));
	}

	void unpack_r8(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint8_t*>(src1);
		dst1[0] = from_unorm(src[0], 255.0F);
		dst1[1] = 0.0F;
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// r8s
	void pack_r8s(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int8_t*>(dst1);
		dst[0] = static_cast<std::int8_t>(to_snorm(src1[0], 127.0F));
	}

	void unpack_r8s(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int8_t*>(src1);
		dst1[0] = from_snorm(src[0], 127.0F);
		dst1[1] = 0.0F;
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// r8i
	void pack_r8i(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int8_t*>(dst1);
		dst[0] = static_cast<std::int8_t>(src1[0]);
	}

	void unpack_r8i(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int8_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
		dst1[1] = 0.0F;
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// r8u
	void pack_r8u(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint8_t*>(dst1);
		dst[0] = static_cast<std::uint8_t>(src1[0]);
	}

	void unpack_r8u(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint8_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
		dst1[1] = 0.0F;
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// rg8
	void pack_rg8(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint8_t*>(dst1);
		dst[0] = static_cast<std::uint8_t>(to_unorm(src1[0], 255.0F));
		dst[1] = static_cast<std::uint8_t>(to_unorm(src1[1], 255.0F));
	}

	void unpack_rg8(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint8_t*>(src1);
		dst1[0] = from_unorm(src[0], 255.0F);
		dst1[1] = from_unorm(src[1], 255.0F);
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// rg8s
	void pack_rg8s(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int8_t*>(dst1);
		dst[0] = static_cast<std::int8_t>(to_snorm(src1[0], 127.0F));
		dst[1] = static_cast<std::int8_t>(to_snorm(src1[1], 127.0F));
	}

	void unpack_rg8s(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int8_t*>(src1);
		dst1[0] = from_snorm(src[0], 127.0F);
		dst1[1] = from_snorm(src[1], 127.0F);
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// rg8i
	void pack_rg8i(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int8_t*>(dst1);
		dst[0] = static_cast<std::int8_t>(src1[0]);
		dst[1] = static_cast<std::int8_t>(src1[1]);
	}

	void unpack_rg8i(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int8_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
		dst1[1] = static_cast<float>(src[1]);
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// rg8u
	void pack_rg8u(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint8_t*>(dst1);
		dst[0] = static_cast<std::uint8_t>(src1[0]);
		dst[1] = static_cast<std::uint8_t>(src1[1]);
	}

	void unpack_rg8u(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint8_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
		dst1[1] = static_cast<float>(src[1]);
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// rgb8
	void pack_rgb8(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint8_t*>(dst1);
		dst[0] = static_cast<std::uint8_t>(to_unorm(src1[0], 255.0F));
		dst[1] = static_cast<std::uint8_t>(to_unorm(src1[1], 255.0F));
		dst[2] = static_cast<std::uint8_t>(to_unorm(src1[2], 255.0F));
	}

	void unpack_rgb8(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint8_t*>(src1);
		dst1[0] = from_unorm(src[0], 255.0F);
		dst1[1] = from_unorm(src[1], 255.0F);
		dst1[2] = from_unorm(src[2], 255.0F);
		dst1[3] = 1.0F;
	}

	// rgb8s
	void pack_rgb8s(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int8_t*>(dst1);
		dst[0] = static_cast<std::int8_t>(to_snorm(src1[0], 127.0F));
		dst[1] = static_cast<std::int8_t>(to_snorm(src1[1], 127.0F));
		dst[2] = static_cast<std::int8_t>(to_snorm(src1[2], 127.0F));
	}

	void unpack_rgb8s(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int8_t*>(src1);
		dst1[0] = from_snorm(src[0], 127.0F);
		dst1[1] = from_snorm(src[1], 127.0F);
		dst1[2] = from_snorm(src[2], 127.0F);
		dst1[3] = 1.0F;
	}

	// rgb8i
	void pack_rgb8i(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int8_t*>(dst1);
		dst[0] = static_cast<std::int8_t>(src1[0]);
		dst[1] = static_cast<std::int8_t>(src1[1]);
		dst[2] = static_cast<std::int8_t>(src1[2]);
	}

	void unpack_rgb8i(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int8_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
		dst1[1] = static_cast<float>(src[1]);
		dst1[2] = static_cast<float>(src[2]);
		dst1[3] = 1.0F;
	}

	// rgb8u
	void pack_rgb8u(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint8_t*>(dst1);
		dst[0] = static_cast<std::uint8_t>(src1[0]);
		dst[1] = static_cast<std::uint8_t>(src1[1]);
		dst[2] = static_cast<std::uint8_t>(src1[2]);
	}

	void unpack_rgb8u(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint8_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
		dst1[1] = static_cast<float>(src[1]);
		dst1[2] = static_cast<float>(src[2]);
		dst1[3] = 1.0F;
	}

	// bgra8
	void pack_bgra8(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint8_t*>(dst1);
		dst[2] = static_cast<std::uint8_t>(to_unorm(src1[0], 255.0F));
		dst[1] = static_cast<std::uint8_t>(to_unorm(src1[1], 255.0F));
		dst[0] = static_cast<std::uint8_t>(to_unorm(src1[2], 255.0F));
		dst[3] = static_cast<std::uint8_t>(to_unorm(src1[3], 255.0F));
	}

	void unpack_bgra8(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint8_t*>(src1);
		dst1[0] = from_unorm(src[2], 255.0F);
		dst1[1] = from_unorm(src[1], 255.0F);
		dst1[2] = from_unorm(src[0], 255.0F);
		dst1[3] = from_unorm(src[3], 255.0F);
	}

	// rgba8
	void pack_rgba8(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint8_t*>(dst1);
		dst[0] = static_cast<std::uint8_t>(to_unorm(src1[0], 255.0F));
		dst[1] = static_cast<std::uint8_t>(to_unorm(src1[1], 255.0F));
		dst[2] = static_cast<std::uint8_t>(to_unorm(src1[2], 255.0F));
		dst[3] = static_cast<std::uint8_t>(to_unorm(src1[3], 255.0F));
	}

	void unpack_rgba8(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint8_t*>(src1);
		dst1[0] = from_unorm(src[0], 255.0F);
		dst1[1] = from_unorm(src[1], 255.0F);
		dst1[2] = from_unorm(src[2], 255.0F);
		dst1[3] = from_unorm(src[3], 255.0F);
	}

	// rgba8s
	void pack_rgba8s(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int8_t*>(dst1);
		dst[0] = static_cast<std::int8_t>(to_snorm(src1[0], 127.0F));
		dst[1] = static_cast<std::int8_t>(to_snorm(src1[1], 127.0F));
		dst[2] = static_cast<std::int8_t>(to_snorm(src1[2], 127.0F));
		dst[3] = static_cast<std::int8_t>(to_snorm(src1[3], 127.0F));
	}

	void unpack_rgba8s(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int8_t*>(src1);
		dst1[0] = from_snorm(src[0], 127.0F);
		dst1[1] = from_snorm(src[1], 127.0F);
		dst1[2] = from_snorm(src[2], 127.0F);
		dst1[3] = from_snorm(src[3], 127.0F);
	}

	// rgba8i
	void pack_rgba8i(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int8_t*>(dst1);
		dst[0] = static_cast<std::int8_t>(src1[0]);
		dst[1] = static_cast<std::int8_t>(src1[1]);
		dst[2] = static_cast<std::int8_t>(src1[2]);
		dst[3] = static_cast<std::int8_t>(src1[3]);
	}

	void unpack_rgba8i(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int8_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
		dst1[1] = static_cast<float>(src[1]);
		dst1[2] = static_cast<float>(src[2]);
		dst1[3] = static_cast<float>(src[3]);
	}

	// rgba8u
	void pack_rgba8u(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint8_t*>(dst1);
		dst[0] = static_cast<std::uint8_t>(src1[0]);
		dst[1] = static_cast<std::uint8_t>(src1[1]);
		dst[2] = static_cast<std::uint8_t>(src1[2]);
		dst[3] = static_cast<std::uint8_t>(src1[3]);
	}

	void unpack_rgba8u(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint8_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
		dst1[1] = static_cast<float>(src[1]);
		dst1[2] = static_cast<float>(src[2]);
		dst1[3] = static_cast<float>(src[3]);
	}

	// r16
	void pack_r16(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint16_t*>(dst1);
		dst[0] = static_cast<std::uint16_t>(to_unorm(src1[0], 65535.0F));
	}

	void unpack_r16(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint16_t*>(src1);
		dst1[0] = from_unorm(src[0], 65535.0F);
		dst1[1] = 0.0F;
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// r16s
	void pack_r16s(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int16_t*>(dst1);
		dst[0] = static_cast<std::int16_t>(to_snorm(src1[0], 32767.0F));
	}

	void unpack_r16s(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int16_t*>(src1);
		dst1[0] = from_snorm(src[0], 32767.0F);
		dst1[1] = 0.0F;
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// r16i
	void pack_r16i(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int16_t*>(dst1);
		dst[0] = static_cast<std::int16_t>(src1[0]);
	}

	void unpack_r16i(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int16_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
		dst1[1] = 0.0F;
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// r16u
	void pack_r16u(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint16_t*>(dst1);
		dst[0] = static_cast<std::uint16_t>(src1[0]);
	}

	void unpack_r16u(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint16_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
	}

	// r16f
	void pack_r16f(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint16_t*>(dst1);
		dst[0] = half_from_float(src1[0]);
	}

	void unpack_r16f(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint16_t*>(src1);
		dst1[0] = half_to_float(src[0]);
		dst1[1] = 0.0F;
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// rg16
	void pack_rg16(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint16_t*>(dst1);
		dst[0] = static_cast<std::uint16_t>(to_unorm(src1[0], 65535.0F));
		dst[1] = static_cast<std::uint16_t>(to_unorm(src1[1], 65535.0F));
	}

	void unpack_rg16(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint16_t*>(src1);
		dst1[0] = from_unorm(src[0], 65535.0F);
		dst1[1] = from_unorm(src[1], 65535.0F);
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// rg16s
	void pack_rg16s(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int16_t*>(dst1);
		dst[0] = static_cast<std::int16_t>(to_snorm(src1[0], 32767.0F));
		dst[1] = static_cast<std::int16_t>(to_snorm(src1[1], 32767.0F));
	}

	void unpack_rg16s(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int16_t*>(src1);
		dst1[0] = from_snorm(src[0], 32767.0F);
		dst1[1] = from_snorm(src[1], 32767.0F);
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// rg16i
	void pack_rg16i(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int16_t*>(dst1);
		dst[0] = static_cast<std::int16_t>(src1[0]);
		dst[1] = static_cast<std::int16_t>(src1[1]);
	}

	void unpack_rg16i(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int16_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
		dst1[1] = static_cast<float>(src[1]);
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// rg16u
	void pack_rg16u(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint16_t*>(dst1);
		dst[0] = static_cast<std::uint16_t>(src1[0]);
		dst[1] = static_cast<std::uint16_t>(src1[1]);
	}

	void unpack_rg16u(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint16_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
		dst1[1] = static_cast<float>(src[1]);
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// rg16f
	void pack_rg16f(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint16_t*>(dst1);
		dst[0] = half_from_float(src1[0]);
		dst[1] = half_from_float(src1[1]);
	}

	void unpack_rg16f(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint16_t*>(src1);
		dst1[0] = half_to_float(src[0]);
		dst1[1] = half_to_float(src[1]);
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// rgba16
	void pack_rgba16(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint16_t*>(dst1);
		dst[0] = static_cast<std::uint16_t>(to_unorm(src1[0], 65535.0F));
		dst[1] = static_cast<std::uint16_t>(to_unorm(src1[1], 65535.0F));
		dst[2] = static_cast<std::uint16_t>(to_unorm(src1[2], 65535.0F));
		dst[3] = static_cast<std::uint16_t>(to_unorm(src1[3], 65535.0F));
	}

	void unpack_rgba16(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint16_t*>(src1);
		dst1[0] = from_unorm(src[0], 65535.0F);
		dst1[1] = from_unorm(src[1], 65535.0F);
		dst1[2] = from_unorm(src[2], 65535.0F);
		dst1[3] = from_unorm(src[3], 65535.0F);
	}

	// rgba16s
	void pack_rgba16s(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int16_t*>(dst1);
		dst[0] = static_cast<std::int16_t>(to_snorm(src1[0], 32767.0F));
		dst[1] = static_cast<std::int16_t>(to_snorm(src1[1], 32767.0F));
		dst[2] = static_cast<std::int16_t>(to_snorm(src1[2], 32767.0F));
		dst[3] = static_cast<std::int16_t>(to_snorm(src1[3], 32767.0F));
	}

	void unpack_rgba16s(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int16_t*>(src1);
		dst1[0] = from_snorm(src[0], 32767.0F);
		dst1[1] = from_snorm(src[1], 32767.0F);
		dst1[2] = from_snorm(src[2], 32767.0F);
		dst1[3] = from_snorm(src[3], 32767.0F);
	}

	// rgba16i
	void pack_rgba16i(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::int16_t*>(dst1);
		dst[0] = static_cast<std::int16_t>(src1[0]);
		dst[1] = static_cast<std::int16_t>(src1[1]);
		dst[2] = static_cast<std::int16_t>(src1[2]);
		dst[3] = static_cast<std::int16_t>(src1[3]);
	}

	void unpack_rgba16i(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::int16_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
		dst1[1] = static_cast<float>(src[1]);
		dst1[2] = static_cast<float>(src[2]);
		dst1[3] = static_cast<float>(src[3]);
	}

	// rgba16u
	void pack_rgba16u(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint16_t*>(dst1);
		dst[0] = static_cast<std::uint16_t>(src1[0]);
		dst[1] = static_cast<std::uint16_t>(src1[1]);
		dst[2] = static_cast<std::uint16_t>(src1[2]);
		dst[3] = static_cast<std::uint16_t>(src1[3]);
	}

	void unpack_rgba16u(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint16_t*>(src1);
		dst1[0] = static_cast<float>(src[0]);
		dst1[1] = static_cast<float>(src[1]);
		dst1[2] = static_cast<float>(src[2]);
		dst1[3] = static_cast<float>(src[3]);
	}

	// rgba16f
	void pack_rgba16f(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint16_t*>(dst1);
		dst[0] = half_from_float(src1[0]);
		dst[1] = half_from_float(src1[1]);
		dst[2] = half_from_float(src1[2]);
		dst[3] = half_from_float(src1[3]);
	}

	void unpack_rgba16f(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint16_t*>(src1);
		dst1[0] = half_to_float(src[0]);
		dst1[1] = half_to_float(src[1]);
		dst1[2] = half_to_float(src[2]);
		dst1[3] = half_to_float(src[3]);
	}

	// r24
	void pack_r24(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint8_t*>(dst1);
		const auto rr = static_cast<std::uint32_t>(to_unorm(src1[0], 16777216.0F));
		dst[0] = static_cast<std::uint8_t>(rr);
		dst[1] = static_cast<std::uint8_t>(rr >> 8);
		dst[2] = static_cast<std::uint8_t>(rr >> 16);
	}

	void unpack_r24(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint8_t*>(src1);
		const std::uint32_t rr = 0 | src[0] | src[1] << 8 | src[2] << 16;

		dst1[0] = from_unorm(rr, 16777216.0F);
		dst1[1] = 0.0F;
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// r24g8
	void pack_r24g8(void* dst1, const float* src1) noexcept
	{
		auto* dst = static_cast<std::uint8_t*>(dst1);
		const auto rr = static_cast<std::uint32_t>(to_unorm(src1[0], 16777216.0F));
		dst[0] = static_cast<std::uint8_t>(rr);
		dst[1] = static_cast<std::uint8_t>(rr >> 8);
		dst[2] = static_cast<std::uint8_t>(rr >> 16);
		dst[3] = static_cast<std::uint8_t>(to_unorm(src1[1], 255.0F));
	}

	void unpack_r24g8(float* dst1, const void* src1) noexcept
	{
		const auto* src = static_cast<const std::uint8_t*>(src1);
		const std::uint32_t rr = 0 | src[0] | src[1] << 8 | src[2] << 16;

		dst1[0] = from_unorm(rr, 16777216.0F);
		dst1[1] = from_unorm(src[3], 255.0F);
		dst1[2] = 0.0F;
		dst1[3] = 1.0F;
	}

	// r32i
	void pack_r32i(void* dst1, const float* src1) noexcept
	{
		std::memcpy(dst1, src1, 4);
	}

	void unpack_r32i(float* dst1, const void* src1) noexcept
	{
		std::memcpy(dst1, src1, 4);
	}

	// r32u
	void pack_r32u(void* dst1, const float* src1) noexcept
	{
		std::memcpy(dst1, src1, 4);
	}

	void unpack_r32u(float* dst1, const void* src1) noexcept
	{
		std::memcpy(dst1, src1, 4);
	}

	// r32f
	void pack_r32f(void* dst1, const float* src1) noexcept
	{
		std::memcpy(dst1, src1, 4);
	}

	void unpack_r32f(float* dst1, const void* src1) noexcept
	{
		std::memcpy(dst1, src1, 4);
	}

	// rg32i
	void pack_rg32i(void* dst1, const float* src1) noexcept
	{
		std::memcpy(dst1, src1, 8);
	}

	void unpack_rg32i(float* dst1, const void* src1) noexcept
	{
		std::memcpy(dst1, src1, 8);
	}

	// rg32u
	void pack_rg32u(void* dst1, const float* src1) noexcept
	{
		std::memcpy(dst1, src1, 8);
	}

	void unpack_rg32u(float* dst1, const void* src1) noexcept
	{
		std::memcpy(dst1, src1, 8);
	}

	// rg32f
	void pack_rg32f(void* dst1, const float* src1) noexcept
	{
		std::memcpy(dst1, src1, 8);
	}

	void unpack_rg32f(float* dst1, const void* src1) noexcept
	{
		std::memcpy(dst1, src1, 8);
	}

	template <std::int32_t mantissabits, std::int32_t expbits>
	void encodergbe(float* dst1, const float* src1) noexcept
	{
		// reference(s):
		// - https://web.archive.org/web/20181126040035/https://www.khronos.org/commands/opengl/extensions/ext/ext_texture_shared_exponent.txt
		//
		const std::int32_t expmax = (1 << expbits) - 1;
		// ReSharper disable once CppRedundantParentheses
		const std::int32_t expbias = (1 << (expbits - 1)) - 1;
		// ReSharper disable once CppRedundantParentheses
		const float sharedexpmax = static_cast<float>(expmax) / static_cast<float>(expmax + 1) * static_cast<float>(1 <<
			(expmax -
				expbias));

		const float rr = std::clamp(src1[0], 0.0F, sharedexpmax);
		const float gg = std::clamp(src1[1], 0.0F, sharedexpmax);
		const float bb = std::clamp(src1[2], 0.0F, sharedexpmax);
		const float mm = std::max(std::max(rr, gg), bb);
		union
		{
			float ff;
			std::uint32_t ui;
		} cast = {mm};
		std::int32_t expshared = static_cast<std::int32_t>(std::max(static_cast<std::uint32_t>(-expbias - 1)
		                                                            , (cast.ui >> 23 & 0xff) - 127)) + 1 + expbias;
		float denom = std::pow(2.0F, static_cast<float>(expshared - expbias - mantissabits));

		if (1 << mantissabits == static_cast<std::int32_t>(std::round(mm / denom)))
		{
			denom *= 2.0F;
			++expshared;
		}

		const float invdenom = 1.0F / denom;
		dst1[0] = std::round(rr * invdenom);
		dst1[1] = std::round(gg * invdenom);
		dst1[2] = std::round(bb * invdenom);
		dst1[3] = static_cast<float>(expshared);
	}

	template <std::int32_t mantissabits, std::int32_t expbits>
	void decodergbe(float* dst1, const float* src1) noexcept
	{
		// ReSharper disable once CppRedundantParentheses
		const std::int32_t expbias = (1 << (expbits - 1)) - 1;
		const float exponent = src1[3] - static_cast<float>(expbias - mantissabits);
		const float scale = std::pow(2.0F, exponent);
		dst1[0] = src1[0] * scale;
		dst1[1] = src1[1] * scale;
		dst1[2] = src1[2] * scale;
	}

	// rgb9e5f
	void pack_rgb9e5f(void* dst1, const float* src1) noexcept
	{
		float tmp[4];
		encodergbe<9, 5>(tmp, src1);

		*static_cast<std::uint32_t*>(dst1) = 0 | static_cast<std::uint32_t>(tmp[0]) | static_cast<std::uint32_t>(tmp[1])
			<< 9 |
			static_cast<std::uint32_t>(tmp[2]) << 18 | static_cast<std::uint32_t>(tmp[3]) << 27;
	}

	void unpack_rgb9e5f(float* dst1, const void* src1) noexcept
	{
		const std::uint32_t pack_ed = *static_cast<const std::uint32_t*>(src1);

		float tmp[4];
		tmp[0] = static_cast<float>(pack_ed & 0x1ff) / 511.0F;
		tmp[1] = static_cast<float>(pack_ed >> 9 & 0x1ff) / 511.0F;
		tmp[2] = static_cast<float>(pack_ed >> 18 & 0x1ff) / 511.0F;
		tmp[3] = static_cast<float>(pack_ed >> 27 & 0x1f);

		decodergbe<9, 5>(dst1, tmp);
	}

	// rgba32i
	void pack_rgba32i(void* dst1, const float* src1) noexcept
	{
		std::memcpy(dst1, src1, 16);
	}

	void unpack_rgba32i(float* dst1, const void* src1) noexcept
	{
		std::memcpy(dst1, src1, 16);
	}

	// rgba32u
	void pack_rgba32u(void* dst1, const float* src1) noexcept
	{
		std::memcpy(dst1, src1, 16);
	}

	void unpack_rgba32u(float* dst1, const void* src1) noexcept
	{
		std::memcpy(dst1, src1, 16);
	}

	// rgba32f
	void pack_rgba32f(void* dst1, const float* src1) noexcept
	{
		std::memcpy(dst1, src1, 16);
	}

	void unpack_rgba32f(float* dst1, const void* src1) noexcept
	{
		std::memcpy(dst1, src1, 16);
	}

	// r5g6b5
	void pack_r5g6b5(void* dst1, const float* src1) noexcept
	{
		*static_cast<std::uint16_t*>(dst1) = 0 | static_cast<std::uint16_t>(to_unorm(src1[0], 31.0F) << 11) |
			static_cast<
				std::uint16_t>(to_unorm(src1[1], 63.0F) << 5) | static_cast<std::uint16_t>(to_unorm(src1[2], 31.0F));
	}

	void unpack_r5g6b5(float* dst1, const void* src1) noexcept
	{
		const std::uint16_t pack_ed = *static_cast<const std::uint16_t*>(src1);
		dst1[0] = static_cast<float>(pack_ed >> 11 & 0x1f) / 31.0F;
		dst1[1] = static_cast<float>(pack_ed >> 5 & 0x3f) / 63.0F;
		dst1[2] = static_cast<float>(pack_ed & 0x1f) / 31.0F;
		dst1[3] = 1.0F;
	}

	// rgba4
	void pack_rgba4(void* dst1, const float* src1) noexcept
	{
		*static_cast<std::uint16_t*>(dst1) = 0 | static_cast<std::uint16_t>(to_unorm(src1[0], 15.0F)) | static_cast<
			std::uint16_t>(
			to_unorm(src1[1], 15.0F) << 4) | static_cast<std::uint16_t>(to_unorm(src1[2], 15.0F) << 8) | static_cast<
			std::uint16_t>(
			to_unorm(src1[3], 15.0F) << 12);
	}

	void unpack_rgba4(float* dst1, const void* src1) noexcept
	{
		const std::uint16_t pack_ed = *static_cast<const std::uint16_t*>(src1);
		dst1[0] = static_cast<float>(pack_ed & 0xf) / 15.0F;
		dst1[1] = static_cast<float>(pack_ed >> 4 & 0xf) / 15.0F;
		dst1[2] = static_cast<float>(pack_ed >> 8 & 0xf) / 15.0F;
		dst1[3] = static_cast<float>(pack_ed >> 12 & 0xf) / 15.0F;
	}

	// rgba4
	void pack_bgra4(void* dst1, const float* src1) noexcept
	{
		*static_cast<std::uint16_t*>(dst1) = 0 | static_cast<std::uint16_t>(to_unorm(src1[0], 15.0F) << 8) | static_cast
			<
				std::uint16_t>(to_unorm(src1[1], 15.0F) << 4) | static_cast<std::uint16_t>(to_unorm(src1[2], 15.0F)) |
			static_cast<
				std::uint16_t>(to_unorm(src1[3], 15.0F) << 12);
	}

	void unpack_bgra4(float* dst1, const void* src1) noexcept
	{
		const std::uint16_t pack_ed = *static_cast<const std::uint16_t*>(src1);
		dst1[0] = static_cast<float>(pack_ed >> 8 & 0xf) / 15.0F;
		dst1[1] = static_cast<float>(pack_ed >> 4 & 0xf) / 15.0F;
		dst1[2] = static_cast<float>(pack_ed & 0xf) / 15.0F;
		dst1[3] = static_cast<float>(pack_ed >> 12 & 0xf) / 15.0F;
	}

	// rgb5a1
	void pack_rgb5a1(void* dst1, const float* src1) noexcept
	{
		*static_cast<std::uint16_t*>(dst1) = 0 | static_cast<std::uint16_t>(to_unorm(src1[0], 31.0F)) | static_cast<
				std::uint16_t>(
				to_unorm(src1[1], 31.0F) << 5) | static_cast<std::uint16_t>(to_unorm(src1[2], 31.0F) << 10) |
			static_cast<
				std::uint16_t>
			(to_unorm(src1[3], 1.0F) << 15);
	}

	void unpack_rgb5a1(float* dst1, const void* src1) noexcept
	{
		const std::uint16_t pack_ed = *static_cast<const std::uint16_t*>(src1);
		dst1[0] = static_cast<float>(pack_ed & 0x1f) / 31.0F;
		dst1[1] = static_cast<float>(pack_ed >> 5 & 0x1f) / 31.0F;
		dst1[2] = static_cast<float>(pack_ed >> 10 & 0x1f) / 31.0F;
		dst1[3] = static_cast<float>(pack_ed >> 14 & 0x1);
	}

	// bgr5a1
	void pack_bgr5a1(void* dst1, const float* src1) noexcept
	{
		*static_cast<std::uint16_t*>(dst1) = 0 | static_cast<std::uint16_t>(to_unorm(src1[0], 31.0F) << 10) |
			static_cast<
				std::uint16_t>(to_unorm(src1[1], 31.0F) << 5) | static_cast<std::uint16_t>(to_unorm(src1[2], 31.0F)) |
			static_cast<
				std::uint16_t>(to_unorm(src1[3], 1.0F) << 15);
	}

	void unpack_bgr5a1(float* dst1, const void* src1) noexcept
	{
		const std::uint16_t pack_ed = *static_cast<const std::uint16_t*>(src1);
		dst1[0] = static_cast<float>(pack_ed >> 10 & 0x1f) / 31.0F;
		dst1[1] = static_cast<float>(pack_ed >> 5 & 0x1f) / 31.0F;
		dst1[2] = static_cast<float>(pack_ed & 0x1f) / 31.0F;
		dst1[3] = static_cast<float>(pack_ed >> 14 & 0x1);
	}

	// rgb10a2
	void pack_rgb10a2(void* dst1, const float* src1) noexcept
	{
		*static_cast<std::uint32_t*>(dst1) = 0 | to_unorm(src1[0], 1023.0F) | to_unorm(src1[1], 1023.0F) << 10 |
			to_unorm(src1[2], 1023.0F) << 20 | to_unorm(src1[3], 3.0F) << 30;
	}

	void unpack_rgb10a2(float* dst1, const void* src1) noexcept
	{
		const std::uint32_t pack_ed = *static_cast<const std::uint32_t*>(src1);
		dst1[0] = static_cast<float>(pack_ed & 0x3ff) / 1023.0F;
		dst1[1] = static_cast<float>(pack_ed >> 10 & 0x3ff) / 1023.0F;
		dst1[2] = static_cast<float>(pack_ed >> 20 & 0x3ff) / 1023.0F;
		dst1[3] = static_cast<float>(pack_ed >> 30 & 0x3) / 3.0F;
	}

	// rg11b10f
	void pack_rg11b10f(void* dst1, const float* src1) noexcept
	{
		*static_cast<std::uint32_t*>(dst1) = 0 | half_from_float(src1[0]) >> 4 & 0x7ff | half_from_float(src1[0]) << 7 &
			0x3ff800 |
			half_from_float(src1[0]) << 17 & 0xffc00000;
	}

	void unpack_rg11b10f(float* dst1, const void* src1) noexcept
	{
		const std::uint32_t pack_ed = *static_cast<const std::uint32_t*>(src1);
		dst1[0] = half_to_float(pack_ed << 4 & 0x7ff0);
		dst1[1] = half_to_float(pack_ed >> 7 & 0x7ff0);
		dst1[2] = half_to_float(pack_ed >> 17 & 0x7fe0);
		dst1[3] = 1.0F;
	}
} // namespace dce // namespace dce
