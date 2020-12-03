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
	/* 3D physics rigidbody */
	class Rigidbody final {
	public:
		Rigidbody() noexcept = default;
		Rigidbody(const Rigidbody&) noexcept = delete;
		Rigidbody(Rigidbody&&) noexcept = default;
		auto operator=(const Rigidbody&) noexcept -> Rigidbody& = delete;
		auto operator=(Rigidbody&&) noexcept -> Rigidbody& = default;
		~Rigidbody() = default;

		float mass = 1.f;
		bool is_kinematic = false;
	};
}
