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

#include "../include/power_ronin/xorshift.hpp"

namespace PowerRonin
{
	auto xorshift32() noexcept -> std::uint32_t
	{
		static auto x32 = UINT32_C(0x12B9B0A1);

		x32 ^= x32 << UINT32_C(0xD);
		x32 ^= x32 >> UINT32_C(0x11);
		x32 ^= x32 << UINT32_C(0x5);
		return x32;
	}

	auto xorshift64() noexcept -> std::uint64_t
	{
		static auto x64 = UINT64_C(0x139408DCBBF7A44);

		x64 ^= x64 << UINT64_C(0xD);
		x64 ^= x64 >> UINT64_C(0x7);
		x64 ^= x64 << UINT64_C(0x11);
		return x64;
	}

	auto xorshift128() noexcept -> std::uint32_t
	{
		static auto x = UINT32_C(0x75BCD15);
		static auto y = UINT32_C(0x159A55E5);
		static auto z = UINT32_C(0x1F123BB5);
		static auto w = UINT32_C(0x5491333);

		const uint32_t t = x ^ x << UINT32_C(0xB);
		x = y;
		y = z;
		z = w;
		w ^= w >> UINT32_C(13) ^ t ^ t >> UINT32_C(0x8);
		return w;
	}
} // namespace PowerRonin // namespace PowerRonin
