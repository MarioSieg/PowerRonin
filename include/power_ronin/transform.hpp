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

#include "mathlib.hpp"

namespace power_ronin
{
	class Transform final
	{
	public:
		Transform() noexcept = default;
		Transform(const Transform&) noexcept = delete;
		Transform(Transform&&) noexcept = default;
		auto operator=(const Transform&) noexcept -> Transform& = delete;
		auto operator=(Transform&&) noexcept -> Transform& = default;
		~Transform() = default;

		SimdVector3<> position = {.0f, .0f, .0f};
		SimdQuaternion<> rotation = {.0f, .0f, .0f, .0f};
		SimdVector3<> scale = {1.f, 1.f, 1.f};

		[[nodiscard]] auto calculate_matrix() const noexcept -> SimdMatrix4x4<>;
		[[nodiscard]] auto forward() const noexcept -> SimdVector3<>;
		[[nodiscard]] auto back() const noexcept -> SimdVector3<>;
		[[nodiscard]] auto up() const noexcept -> SimdVector3<>;
		[[nodiscard]] auto down() const noexcept -> SimdVector3<>;
		[[nodiscard]] auto left() const noexcept -> SimdVector3<>;
		[[nodiscard]] auto right() const noexcept -> SimdVector3<>;
	};
}
