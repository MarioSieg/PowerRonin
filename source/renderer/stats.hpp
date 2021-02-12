#pragma once

namespace PowerRonin
{
	class Runtime;
	class Diagnostics;
	class AsyncProtocol;

	namespace Renderer
	{
		extern void poll_limits(Diagnostics& _diag) noexcept;
		extern void dump_limits(AsyncProtocol& _proto);
		extern void poll_stats(Diagnostics& _diag) noexcept;
		extern void render_stats(const Runtime& _runtime);
	}
}
