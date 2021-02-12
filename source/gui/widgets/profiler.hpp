#pragma once

#if AUTO_TEC

namespace PowerRonin
{
	class Chrono;
	class Diagnostics;

	namespace Interface::widgets
	{
		class Profiler final
		{
		public:
			void update(bool& _show, const Diagnostics& _diag, const Chrono& _chrono) const;
		};
	} // namespace gui::widgets
} // namespace PowerRonin // namespace PowerRonin

#endif
