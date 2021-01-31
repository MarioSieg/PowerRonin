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

#include <cstdint>

namespace PowerRonin
{
	/// <summary>
	/// Allocate a managed object.
	/// </summary>
	/// <param name="domain">The mono domain.</param>
	/// <param name="klass">The mono class.</param>
	/// <param name="ctor">The constructor method.</param>
	/// <param name="ctorArgs">The constructor args.</param>
	/// <param name="isPinned">If true object is pinned when using a moving GC.</param>
	/// <returns>The GC handle.</returns>
	[[nodiscard]]
	extern auto MoAlloc(void* const domain, void* const klass, void* const ctor = nullptr, void** const ctorArgs = nullptr, const bool isPinned = false) -> std::uint32_t;

	/// <summary>
	/// Deallocate a managed object.
	/// </summary>
	/// <param name="gcRef">The gc reference to remove.</param>
	/// <returns></returns>
	extern void MoDealloc(std::uint32_t& gcRef) noexcept;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="gcRef">The GC handle to unwrap.</param>
	/// <returns>The mono object behind the gc handle.</returns>
	[[nodiscard]]
	extern auto MoUnwrap(const std::uint32_t gcRef) noexcept -> void*;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="gcRef">The GC handle to unbox.</param>
	/// <returns>The real object behind the mono object and gc handle.</returns>
	[[nodiscard]]
	extern auto MoUnbox(const std::uint32_t gcRef) noexcept -> void*;
}
