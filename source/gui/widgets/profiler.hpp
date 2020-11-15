// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: profiler.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 09.11.2020 06:18

#pragma once

namespace dce {
	class Chrono;
	class Diagnostics;

	namespace gui::widgets {
		class Profiler final {
		public:
			void update(bool &_show, const Diagnostics &_diag, const Chrono &_chrono) const;
		};
	} // namespace gui::widgets
} // namespace dce // namespace dce
