#pragma once

#include <cstdint>

namespace dce {
	/// <summary>
	/// Represents any x64* GPR register.
	/// </summary>
	union RAX {
		struct EAX final {
			struct AX final {
				union {
					std::uint8_t ah;
					std::uint8_t al;
				};

				std::uint16_t value;
			} ax;

			std::uint32_t value;
		} eax;

		std::uint64_t value = 0;
	};

	static_assert(sizeof(RAX) == 8);

	/// <summary>
	/// Represents any x64 MMX* register.
	/// </summary>
	struct MMX0 final {
		std::uint64_t value = 0;
	};

	static_assert(sizeof(MMX0) == 8);

	/// <summary>
	/// Represents any SSE XMM* register.
	/// </summary>
	struct XMM0 final {
		std::uint64_t hi = 0;
		std::uint64_t lo = 0;
	};

	static_assert(sizeof(XMM0) == 16);

	/// <summary>
	/// Represents any AVX YMM* register.
	/// </summary>
	union YMM0 final {
		struct {
			std::uint64_t hi0;
			std::uint64_t lo0;
			std::uint64_t hi1;
			std::uint64_t lo1;
		};

		struct {
			XMM0 x_alpha;
			XMM0 x_beta;
		};
	};

	static_assert(sizeof(YMM0) == 32);

	/// <summary>
	/// Represents any AVX-512 ZMM* register.
	/// </summary>
	union ZMM0 final {
		struct {
			std::uint64_t hi0;
			std::uint64_t lo0;
			std::uint64_t hi1;
			std::uint64_t lo1;
			std::uint64_t hi2;
			std::uint64_t lo2;
			std::uint64_t hi3;
			std::uint64_t lo3;
		};

		struct {
			XMM0 z_alpha;
			XMM0 z_beta;
			XMM0 z_gamma;
			XMM0 z_delta;
		};

		struct {
			YMM0 y_alpha;
			YMM0 y_beta;
		};
	};

	static_assert(sizeof(ZMM0) == 64);

	/// <summary>
	/// Contains all GPR registers.
	/// </summary>
	enum class GprRegisters {
		RAX,
		RBX,
		RCX,
		RDX,
		RBP,
		RSI,
		RDI,
		RSP,
		R8,
		R9,
		R10,
		R11,
		R12,
		R13,
		R14,
		R15,
	};

	/// <summary>
	/// Load the value from the hardware register.
	/// If the arch is not x86_64 or the compiler is MSVC it just returns 0.
	/// Use clang to compile release builds!
	/// </summary>
	/// <param name="_out"></param>
	/// <param name="_target"></param>
	/// <returns></returns>
	extern void query_gpr(RAX& _out, const GprRegisters _target) noexcept;

	/// <summary>
	/// Contains all MMX registers.
	/// </summary>
	enum class MmxRegisters {
		XMMX0_FPR0,
		XMMX1_FPR1,
		XMMX2_FPR2,
		XMMX3_FPR3,
		XMMX4_FPR4,
		XMMX5_FPR5,
		XMMX6_FPR6,
		XMMX7_FPR7,
	};

	/// <summary>
	/// Contains SSE registers.
	/// </summary>
	enum class SseRegisters {
		XMM0,
		XMM1,
		XMM2,
		XMM3,
		XMM4,
		XMM5,
		XMM6,
		XMM7,
		XMM8,
		XMM9,
		XMM10,
		XMM11,
		XMM12,
		XMM13,
		XMM14,
		XMM15,
	};

	/// <summary>
	/// Contains all AVX registers.
	/// </summary>
	enum class AvxRegisters {
		YMM0,
		YMM1,
		YMM2,
		YMM3,
		YMM4,
		YMM5,
		YMM6,
		YMM7,
		YMM8,
		YMM9,
		YMM10,
		YMM11,
		YMM12,
		YMM13,
		YMM14,
		YMM15,
	};

	/// <summary>
	/// Contains all AVX-512 registers.
	/// </summary>
	enum class Avx512Registers {
		ZMM0,
		ZMM1,
		ZMM2,
		ZMM3,
		ZMM4,
		ZMM5,
		ZMM6,
		ZMM7,
		ZMM8,
		ZMM9,
		ZMM10,
		ZMM11,
		ZMM12,
		ZMM13,
		ZMM14,
		ZMM15,
		ZMM16,
		ZMM17,
		ZMM18,
		ZMM19,
		ZMM20,
		ZMM21,
		ZMM22,
		ZMM23,
		ZMM24,
		ZMM25,
		ZMM26,
		ZMM27,
		ZMM28,
		ZMM29,
		ZMM30,
		ZMM31,
	};
}
