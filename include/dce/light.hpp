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

#include "mathlib.hpp"

namespace dce {
	/// <summary>
	/// Represents a light.
	/// </summary>
	class Light final {
	public:
		Light() noexcept = default;
		Light(const Light&) noexcept = delete;
		Light(Light&&) noexcept = default;
		auto operator=(const Light&) noexcept -> Light& = delete;
		auto operator=(Light&&) noexcept -> Light& = default;
		~Light() = default;

		/// <summary>
		/// The type of the light.
		/// </summary>
		enum class Type {
			DIRECTIONAL,
			SPOT,
			POINT
		} type = Type::DIRECTIONAL;

		/// <summary>
		/// The light color.
		/// </summary>
		Color<> color = {1.f, 1.f, 1.f, 1.f};

		/// <summary>
		/// The light intensity in Lux.
		/// </summary>
		float intensity = 1.f;
	};
}
