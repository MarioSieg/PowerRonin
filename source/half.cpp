// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../include/dce/half.hpp"

namespace dce {
	auto half_from_float(const float x) noexcept -> std::uint16_t {
		const union {
			std::uint32_t ui;
			float flt;
		} ftou{.flt = x};

		const std::uint32_t one = 0x00000001;
		const std::uint32_t f_s_mask = 0x80000000;
		const std::uint32_t f_e_mask = 0x7f800000;
		const std::uint32_t f_m_mask = 0x007fffff;
		const std::uint32_t f_m_hidden_bit = 0x00800000;
		const std::uint32_t f_m_round_bit = 0x00001000;
		const std::uint32_t f_snan_mask = 0x7fc00000;
		const std::uint32_t f_e_pos = 0x00000017;
		const std::uint32_t h_e_pos = 0x0000000a;
		const std::uint32_t h_e_mask = 0x00007c00;
		const std::uint32_t h_snan_mask = 0x00007e00;
		const std::uint32_t h_e_mask_value = 0x0000001f;
		const std::uint32_t f_h_s_pos_offset = 0x00000010;
		const std::uint32_t f_h_bias_offset = 0x00000070;
		const std::uint32_t f_h_m_pos_offset = 0x0000000d;
		const std::uint32_t h_nan_min = 0x00007c01;
		const std::uint32_t f_h_e_biased_flag = 0x0000008f;
		const std::uint32_t f_s = ftou.ui & f_s_mask;
		const std::uint32_t f_e = ftou.ui & f_e_mask;
		const auto h_s = static_cast<uint16_t>(f_s >> f_h_s_pos_offset);
		const std::uint32_t f_m = ftou.ui & f_m_mask;
		const auto f_e_amount = static_cast<uint16_t>(f_e >> f_e_pos);
		const std::uint32_t f_e_half_bias = f_e_amount - f_h_bias_offset;
		const std::uint32_t f_snan = ftou.ui & f_snan_mask;
		const std::uint32_t f_m_round_mask = f_m & f_m_round_bit;
		const std::uint32_t f_m_round_offset = f_m_round_mask << one;
		const std::uint32_t f_m_rounded = f_m + f_m_round_offset;
		const std::uint32_t f_m_denorm_sa = one - f_e_half_bias;
		const std::uint32_t f_m_with_hidden = f_m_rounded | f_m_hidden_bit;
		const std::uint32_t f_m_denorm = f_m_with_hidden >> f_m_denorm_sa;
		const std::uint32_t h_m_denorm = f_m_denorm >> f_h_m_pos_offset;
		const std::uint32_t f_m_rounded_overflow = f_m_rounded & f_m_hidden_bit;
		const std::uint32_t m_nan = f_m >> f_h_m_pos_offset;
		const std::uint32_t h_em_nan = h_e_mask | m_nan;
		const std::uint32_t h_e_norm_overflow_offset = f_e_half_bias + 1;
		const std::uint32_t h_e_norm_overflow = h_e_norm_overflow_offset << h_e_pos;
		const std::uint32_t h_e_norm = f_e_half_bias << h_e_pos;
		const std::uint32_t h_m_norm = f_m_rounded >> f_h_m_pos_offset;
		const std::uint32_t h_em_norm = h_e_norm | h_m_norm;
		const std::uint32_t is_h_ndenorm_msb = f_h_bias_offset - f_e_amount;
		const std::uint32_t is_f_e_flagged_msb = f_h_e_biased_flag - f_e_half_bias;
		const std::uint32_t is_h_denorm_msb = ~is_h_ndenorm_msb;
		const std::uint32_t is_f_m_eqz_msb = f_m - 1;
		const std::uint32_t is_h_nan_eqz_msb = m_nan - 1;
		const std::uint32_t is_f_inf_msb = is_f_e_flagged_msb & is_f_m_eqz_msb;
		const std::uint32_t is_f_nan_underflow_msb = is_f_e_flagged_msb & is_h_nan_eqz_msb;
		const std::uint32_t is_e_overflow_msb = h_e_mask_value - f_e_half_bias;
		const std::uint32_t is_h_inf_msb = is_e_overflow_msb | is_f_inf_msb;
		const std::uint32_t is_f_nsnan_msb = f_snan - f_snan_mask;
		const std::uint32_t is_m_norm_overflow_msb = -static_cast<std::int32_t>(f_m_rounded_overflow);
		const std::uint32_t is_f_snan_msb = ~is_f_nsnan_msb;
		const std::uint32_t h_em_overflow_result = uint32_sels(is_m_norm_overflow_msb, h_e_norm_overflow, h_em_norm);
		const std::uint32_t h_em_nan_result = uint32_sels(is_f_e_flagged_msb, h_em_nan, h_em_overflow_result);
		const std::uint32_t h_em_nan_underflow_result = uint32_sels(is_f_nan_underflow_msb, h_nan_min, h_em_nan_result);
		const std::uint32_t h_em_inf_result = uint32_sels(is_h_inf_msb, h_e_mask, h_em_nan_underflow_result);
		const std::uint32_t h_em_denorm_result = uint32_sels(is_h_denorm_msb, h_m_denorm, h_em_inf_result);
		const std::uint32_t h_em_snan_result = uint32_sels(is_f_snan_msb, h_snan_mask, h_em_denorm_result);
		const std::uint32_t h_result = h_s | h_em_snan_result;

		return static_cast<uint16_t>(h_result);
	}

	auto half_to_float(const uint16_t x) noexcept -> float {
		const std::uint32_t h_e_mask = 0x00007c00;
		const std::uint32_t h_m_mask = 0x000003ff;
		const std::uint32_t h_s_mask = 0x00008000;
		const std::uint32_t h_f_s_pos_offset = 0x00000010;
		const std::uint32_t h_f_e_pos_offset = 0x0000000d;
		const std::uint32_t h_f_bias_offset = 0x0001c000;
		const std::uint32_t f_e_mask = 0x7f800000;
		const std::uint32_t f_m_mask = 0x007fffff;
		const std::uint32_t h_f_e_denorm_bias = 0x0000007e;
		const std::uint32_t h_f_m_denorm_sa_bias = 0x00000008;
		const std::uint32_t f_e_pos = 0x00000017;
		const std::uint32_t h_e_mask_minus_one = 0x00007bff;
		const std::uint32_t h_e = x & h_e_mask;
		const std::uint32_t h_m = x & h_m_mask;
		const std::uint32_t h_s = x & h_s_mask;
		const std::uint32_t h_e_f_bias = h_e + h_f_bias_offset;
		const std::uint32_t h_m_nlz = uint32_cntlz(h_m);
		const std::uint32_t f_s = h_s << h_f_s_pos_offset;
		const std::uint32_t f_e = h_e_f_bias << h_f_e_pos_offset;
		const std::uint32_t f_m = h_m << h_f_e_pos_offset;
		const std::uint32_t f_em = f_e | f_m;
		const std::uint32_t h_f_m_sa = h_m_nlz - h_f_m_denorm_sa_bias;
		const std::uint32_t f_e_denorm_unpacked = h_f_e_denorm_bias - h_f_m_sa;
		const std::uint32_t h_f_m = h_m << h_f_m_sa;
		const std::uint32_t f_m_denorm = h_f_m & f_m_mask;
		const std::uint32_t f_e_denorm = f_e_denorm_unpacked << f_e_pos;
		const std::uint32_t f_em_denorm = f_e_denorm | f_m_denorm;
		const std::uint32_t f_em_nan = f_e_mask | f_m;
		const std::uint32_t is_e_eqz_msb = h_e - 1;
		const std::uint32_t is_m_nez_msb = -static_cast<std::int32_t>(h_m);
		const std::uint32_t is_e_flagged_msb = h_e_mask_minus_one - h_e;
		const std::uint32_t is_zero_msb = is_e_eqz_msb & ~is_m_nez_msb;
		const std::uint32_t is_inf_msb = is_e_flagged_msb & ~is_m_nez_msb;
		const std::uint32_t is_denorm_msb = is_m_nez_msb & is_e_eqz_msb;
		const std::uint32_t is_nan_msb = is_e_flagged_msb & is_m_nez_msb;
		const std::uint32_t is_zero = static_cast<int32_t>(is_zero_msb) >> 31;
		const std::uint32_t f_zero_result = f_em & ~is_zero;
		const std::uint32_t f_denorm_result = uint32_sels(is_denorm_msb, f_em_denorm, f_zero_result);
		const std::uint32_t f_inf_result = uint32_sels(is_inf_msb, f_e_mask, f_denorm_result);
		const std::uint32_t f_nan_result = uint32_sels(is_nan_msb, f_em_nan, f_inf_result);
		const std::uint32_t f_result = f_s | f_nan_result;

		const union {
			std::uint32_t ui;
			float flt;
		} utof{.ui = f_result};
		return utof.flt;
	}
} // namespace dce // namespace dce
