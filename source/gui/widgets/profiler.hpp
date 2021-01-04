#pragma once

namespace power_ronin
{
	class Chrono;
	class Diagnostics;

	namespace gui::widgets
	{
		class Profiler final
		{
		public:
			void update(bool& _show, const Diagnostics& _diag, const Chrono& _chrono) const;
		};
	} // namespace gui::widgets
} // namespace power_ronin // namespace power_ronin
