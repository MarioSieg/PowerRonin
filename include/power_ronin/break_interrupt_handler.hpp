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

namespace PowerRonin
{
	struct ScopedVectoredExceptionHandler final
	{
		ScopedVectoredExceptionHandler();
		ScopedVectoredExceptionHandler(const ScopedVectoredExceptionHandler&) = delete;
		ScopedVectoredExceptionHandler(ScopedVectoredExceptionHandler&&) = delete;
		auto operator=(const ScopedVectoredExceptionHandler&) = delete;
		auto operator=(ScopedVectoredExceptionHandler&&) = delete;
		~ScopedVectoredExceptionHandler();

	private:
		void* handle = nullptr;
	};
}
