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

namespace power_ronin
{
	/// <summary>
	/// Allocate a managed object.
	/// </summary>
	/// <param name="_domain">The mono domain.</param>
	/// <param name="_class">The mono class.</param>
	/// <param name="_ctor">The constructor method.</param>
	/// <param name="_ctor_args">The constructor args.</param>
	/// <param name="_is_pinned">If true object is pinned when using a moving GC.</param>
	/// <returns>The GC handle.</returns>
	[[nodiscard]]
	extern auto mo_alloc(void* const _domain, void* const _class, void* const _ctor = nullptr, void** const _ctor_args = nullptr, const bool _is_pinned = false) -> std::uint32_t;

	/// <summary>
	/// Deallocate a managed object.
	/// </summary>
	/// <param name="_gc_ref">The gc reference to remove.</param>
	/// <returns></returns>
	extern void mo_dealloc(std::uint32_t& _gc_ref) noexcept;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="_gc_ref">The GC handle to unwrap.</param>
	/// <returns>The mono object behind the gc handle.</returns>
	[[nodiscard]]
	extern auto mo_unwrap(const std::uint32_t _gc_ref) noexcept -> void*;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="_gc_ref">The GC handle to unbox.</param>
	/// <returns>The real object behind the mono object and gc handle.</returns>
	[[nodiscard]]
	extern auto mo_unbox(const std::uint32_t _gc_ref) noexcept -> void*;
}
