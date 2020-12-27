#pragma once

namespace dce {
	class Runtime;
	class Diagnostics;
	class AsyncProtocol;

	namespace renderer {
		extern void get_limits(Diagnostics& _diag) noexcept;
		extern void dump_limits(AsyncProtocol& _proto);
		extern void get_runtime_stats(Diagnostics& _diag) noexcept;
		extern void render_stats(const Runtime& _runtime);
	}
}
