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
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../include/dce/cpu_registers.hpp"
#include "../include/dce/env.hpp"

namespace dce {

	void query_gpr(RAX& _out, const GprRegisters _target) noexcept {
#if !CPU_X86 || COM_MSVC
		_out = {0};
#else
		switch (_target) {
		case GprRegisters::RAX: {
#if COM_GCC | COM_CLANG
			std::uint64_t x;
			asm volatile("\t movq %%rax, %0" : "=r"(x));
			_out.value = x;
		}
		break;
#endif
		}
#endif
	}
}
