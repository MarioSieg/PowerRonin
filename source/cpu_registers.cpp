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
