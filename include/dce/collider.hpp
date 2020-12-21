#pragma once

#include "mathlib.hpp"

namespace dce {
	/* Represents a physical collider. */
	class Collider final {
	public:
		Collider() noexcept = default;
		Collider(const Collider&) noexcept = delete;
		Collider(Collider&&) noexcept = default;
		auto operator=(const Collider&) noexcept -> Collider& = delete;
		auto operator=(Collider&&) noexcept -> Collider& = default;
		~Collider() = default;

		union ColliderData {
			/* Box collider data. */
			struct {
				Vector3<> half_extents;
			} box = {};

			/* Sphere collider data. */
			struct {
				float radius = 10.f;
			} sphere;
		} data = {.box = {.half_extents = {20.f, 20.f, 20.f}}};

		/* Discriminator */
		enum class Type : std::uint8_t {
			BOX,
			SPHERE
		} type = Type::BOX;
	};
}
