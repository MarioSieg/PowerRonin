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

#include <cstddef>

namespace PowerRonin
{
	class Diagnostics final
	{
	public:
		struct
		{
			std::size_t MaxVram = 0;
			std::size_t UsedVram = 0;

			std::size_t MaxDrawCalls = 0;
			std::size_t UsedDrawCalls = 0;

			std::size_t MaxBlitCalls = 0;
			std::size_t UsedBlitCalls = 0;

			std::size_t MaxTextures = 0;
			std::size_t UsedTextures = 0;

			std::size_t MaxShaders = 0;
			std::size_t UsedShaders = 0;

			std::size_t MaxPrograms = 0;
			std::size_t UsedPrograms = 0;

			std::size_t MaxUniforms = 0;
			std::size_t UsedUniforms = 0;

			std::size_t MaxVertexBuffers = 0;
			std::size_t UsedVertexBuffers = 0;

			std::size_t MaxIndexBuffers = 0;
			std::size_t UsedIndexBuffers = 0;

			std::size_t MaxDynamicVertexBuffers = 0;
			std::size_t UsedDynamicVertexBuffers = 0;

			std::size_t MaxDynamicIndexBuffers = 0;
			std::size_t UsedDynamicIndexBuffers = 0;

			std::size_t MaxFrameBuffers = 0;
			std::size_t UsedFrameBuffers = 0;

			std::size_t SceneryMeshDrawCalls = 0;
		} Graphics = {};
	};
} // namespace PowerRonin // namespace PowerRonin
