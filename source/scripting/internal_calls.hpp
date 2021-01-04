#pragma once

namespace power_ronin
{
	class Runtime;
}

namespace power_ronin::scripting
{
	extern void register_basic_internal_calls(Runtime& _rt);
}
