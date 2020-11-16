// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: stats.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 15.11.2020 21:36

#pragma once

namespace dce {
	class Diagnostics;
	class AsyncProtocol;

	namespace renderer {
		extern void get_limits(Diagnostics &_diag) noexcept;
		extern void dump_limits(AsyncProtocol &_proto);
		extern void get_runtime_stats(Diagnostics &_diag) noexcept;
	}
}
