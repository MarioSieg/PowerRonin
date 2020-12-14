#pragma once

namespace dce {
	class Runtime;
}

namespace dce::scripting {
	extern void register_basic_internal_calls(Runtime& _rt);
}
