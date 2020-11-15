// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: stats.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 14.11.2020 13:59

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
