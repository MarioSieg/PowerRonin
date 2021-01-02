#pragma once

namespace dce
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
} // namespace dce // namespace dce
