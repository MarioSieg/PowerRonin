// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma once

namespace dce {
	class Diagnostics;
	class AsyncProtocol;

	namespace renderer {
		extern void get_limits(Diagnostics& _diag) noexcept;
		extern void dump_limits(AsyncProtocol& _proto);
		extern void get_runtime_stats(Diagnostics& _diag) noexcept;
	}
}
