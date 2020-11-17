// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: collider.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 17.11.2020 11:21

#pragma once

#include "mathlib.hpp"

namespace dce {
	/* Represents a physics collider. */
	class Collider final {
	public:
		union ColliderData {
			/* Box collider data. */
			struct {
				Vec3 half_extents;
			} box;

			/* Sphere collider data. */
			struct {
				float radius = 10.f;
			} sphere;
		} data = {.box = {.half_extents = {20.f, 20.f, 20.f}}};

		/* Discriminator */
		enum class Type : std::uint8_t {
			BOX
			, SPHERE
		} type = Type::BOX;
	};
}
