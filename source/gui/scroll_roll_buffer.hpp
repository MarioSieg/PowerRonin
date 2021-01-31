// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#pragma once

#include "gui_headers.hpp"

namespace PowerRonin::Interface
{
	// utility structure for realtime plot
	struct ScrollingBuffer final
	{
		int max_size;
		int offset;
		ImVector<ImVec2> data;

		ScrollingBuffer();

		void add_point(float _x, float _y);
		void erase();
	};

	// Utility structure for realtime plot.
	struct RollingBuffer
	{
		float span;
		ImVector<ImVec2> data;

		RollingBuffer();

		void add_point(float _x, float _y);
	};
} // namespace PowerRonin::gui::widgets // namespace PowerRonin::gui::widgets
